// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <os/os.h>
#include <os/mem.h>
#include <components/log.h>
#include <components/video_types.h>
#include "media_evt.h"
#include "wlan_ui_pub.h"
#include "media_app.h"
#include "transfer_act.h"
#include "storage_act.h"

#if (CONFIG_CACHE_ENABLE)
#include "cache.h"
#endif

#include "media_mailbox_list_util.h"

#define TAG "trs_app"

#define LOGI(...) BK_LOGW(TAG, ##__VA_ARGS__)
#define LOGW(...) BK_LOGW(TAG, ##__VA_ARGS__)
#define LOGE(...) BK_LOGE(TAG, ##__VA_ARGS__)
#define LOGD(...) BK_LOGD(TAG, ##__VA_ARGS__)

static beken_thread_t transfer_app_task = NULL;
static beken_queue_t transfer_app_msg_que = NULL;
static transfer_data_t *transfer_app_data = NULL;
static video_setup_t *transfer_app_config = NULL;
static frame_buffer_t *current_frame = NULL;
static media_mailbox_msg_t *transfer_app_node = NULL;
static bool transfer_app_task_running = false;

#ifdef CONFIG_INTEGRATION_DOORBELL
const media_transfer_cb_t *media_transfer_callback = NULL;
#endif

void os_memcpy_word_reverse(uint32_t *dst, uint32_t *src, uint32_t size)
{
	uint32_t i = 0;
	size /= 4;
	for (i = 0; i < size; i++)
	{
		dst[i] = WORD_REVERSE(src[i]);
	}
}

static bk_err_t transfer_app_task_send_msg(uint8_t type, uint32_t data)
{
	bk_err_t ret = kNoErr;
	trs_task_msg_t msg;

	if (transfer_app_msg_que)
	{
		msg.type = type;
		msg.data = data;

		ret = rtos_push_to_queue(&transfer_app_msg_que, &msg, BEKEN_NO_WAIT);
		if (kNoErr != ret)
		{
			LOGE("transfer_app_task_send_msg failed, type:%d\r\n", type);
			return kNoResourcesErr;
		}

		return ret;
	}
	return kGeneralErr;
}

int send_frame_buffer_packet(uint8_t *data, uint32_t size, uint32_t retry_max)
{
	int ret = BK_FAIL;

#ifdef CONFIG_INTEGRATION_DOORBELL

	if (media_transfer_callback == NULL)
		return ret;

	if (media_transfer_callback->prepare)
	{
		media_transfer_callback->prepare(data, size);
	}

	//LOGI("%02x %02x %02x %02x, %d\r\n", data[0], data[1], data[2], data[3], size);

	do
	{
		ret = media_transfer_callback->send(data, size);
#else

	if (!transfer_app_config->send_func)
	{
		return ret;
	}

	do
	{
		ret = transfer_app_config->send_func(data, size);
#endif
		if (ret == size)
		{
			//rtos_delay_milliseconds(1);
			break;
		}
		rtos_delay_milliseconds(TRAN_RETRY_DELAY_TIME);
	}
	while (retry_max-- && transfer_app_task_running);

	return ret == size ? BK_OK : BK_FAIL;
}

static void transfer_app_task_send_frame(frame_buffer_t *buffer)
{
	int ret = kNoErr;

	uint32_t i;
	uint32_t count = buffer->length / transfer_app_config->pkt_size;
	uint32_t tail = buffer->length % transfer_app_config->pkt_size;

	uint8_t *src_address = buffer->frame;
	LOGD("seq: %u, length: %u, size: %u\n", buffer->sequence, buffer->length, buffer->size);
	transfer_app_data->id = (buffer->sequence & 0xFF);
	transfer_app_data->eof = 0;
	transfer_app_data->cnt = 0;//package seq num
	transfer_app_data->size = count + (tail ? 1 : 0);//one frame package counts

	for (i = 0; i < count && transfer_app_task_running; i++)
	{
		transfer_app_data->cnt = i + 1;

		if ((tail == 0) && (i == count - 1))
		{
			transfer_app_data->eof = 1;
		}

		if (buffer->fmt == PIXEL_FMT_DVP_H264) {
			os_memcpy_word_reverse((uint32_t *)transfer_app_data->data, (uint32_t *)(src_address + (transfer_app_config->pkt_size * i)),
									transfer_app_config->pkt_size);
		} else {
			os_memcpy_word((uint32_t *)transfer_app_data->data, (uint32_t *)(src_address + (transfer_app_config->pkt_size * i)),
							transfer_app_config->pkt_size);
		}

		ret = send_frame_buffer_packet((uint8_t *)transfer_app_data, transfer_app_config->pkt_size + transfer_app_config->pkt_header_size,
										TRAN_MAX_RETRY_TIME);
		if (ret != BK_OK)
		{
			LOGD("send failed\n");
		}
	}

	if (tail)
	{
		transfer_app_data->eof = 1;
		transfer_app_data->cnt = count + 1;

		/* fix for psram 4bytes alignment */
		if (buffer->fmt == PIXEL_FMT_DVP_H264) {
			os_memcpy_word_reverse((uint32_t *)transfer_app_data->data, (uint32_t *)(src_address + (transfer_app_config->pkt_size * i)),
									(tail % 4) ? ((tail / 4 + 1) * 4) : tail);
		} else {
			os_memcpy_word((uint32_t *)transfer_app_data->data, (uint32_t *)(src_address + (transfer_app_config->pkt_size * i)),
							(tail % 4) ? ((tail / 4 + 1) * 4) : tail);
		}

		if (transfer_app_config->send_type ==  TVIDEO_SND_UDP)
			ret = send_frame_buffer_packet((uint8_t *)transfer_app_data, tail + transfer_app_config->pkt_header_size, TRAN_MAX_RETRY_TIME);
		else
			ret = send_frame_buffer_packet((uint8_t *)transfer_app_data, VIDEO_TCP_TRAN_LEN, TRAN_MAX_RETRY_TIME);

		if (ret != BK_OK)
		{
			LOGD("send failed\n");
		}
	}

	LOGD("length: %u, tail: %u, count: %u\n", buffer->length, tail, count);

}

static void transfer_app_task_send_handle(uint32_t param)
{
	if (current_frame)
	{
#if (CONFIG_CACHE_ENABLE)
		flush_dcache(current_frame->frame, current_frame->size);
#endif

		transfer_app_task_send_frame(current_frame);

		current_frame = NULL;

		// send finish notify to cp1
		msg_send_rsp_to_media_app_mailbox(transfer_app_node, BK_OK);
	}
}

static void transfer_app_task_entry(beken_thread_arg_t data)
{
	int ret = kNoErr;

	transfer_app_task_running = true;

	while (1)
	{
		trs_task_msg_t msg;
		ret = rtos_pop_from_queue(&transfer_app_msg_que, &msg, BEKEN_WAIT_FOREVER);
		if (kNoErr == ret)
		{
			switch (msg.type)
			{
				case TRS_TRANSFER_DATA:
					transfer_app_task_send_handle(msg.data);
					break;

				case TRS_TRANSFER_EXIT:
					goto exit;
					break;

				default:
					break;
			}
		}
	};

exit:

	LOGI("transfer_app_task exit\n");

	if (transfer_app_config)
	{
		os_free(transfer_app_config);
		transfer_app_config = NULL;
	}

#ifdef CONFIG_INTEGRATION_DOORBELL
	media_transfer_callback = NULL;
	transfer_app_data = NULL;
#else
	if (transfer_app_data)
	{
		os_free(transfer_app_data);
		transfer_app_data = NULL;
	}
#endif

	current_frame = NULL;
	transfer_app_node = NULL;

	transfer_app_task_running = false;

	rtos_deinit_queue(&transfer_app_msg_que);
	transfer_app_msg_que = NULL;

	transfer_app_task = NULL;
	rtos_delete_thread(NULL);
}

#ifdef CONFIG_INTEGRATION_DOORBELL
bk_err_t transfer_app_task_init(const media_transfer_cb_t *cb)
{
	int ret = BK_OK;

	if (transfer_app_task_running)
	{
		LOGI("transfer_app_task already init!\r\n");
		return ret;
	}

	media_transfer_callback = cb;

	LOGI("%s cb: %p ++\n", __func__, media_transfer_callback);

	if (transfer_app_config == NULL)
	{
		transfer_app_config = (video_setup_t *)os_malloc(sizeof(video_setup_t));
		if (transfer_app_config == NULL)
		{
			LOGE("% malloc failed\r\n", __func__);
			return BK_ERR_NO_MEM;
		}

		os_memset(transfer_app_config, 0, sizeof(video_setup_t));
		transfer_app_config->pkt_header_size = sizeof(transfer_data_t);
	}

	LOGI("%s, %p, %d\r\n", __func__, media_transfer_callback->get_tx_buf, __LINE__);

	if (media_transfer_callback->get_tx_buf)
	{
		transfer_app_data = media_transfer_callback->get_tx_buf();
		transfer_app_config->pkt_size = media_transfer_callback->get_tx_size() - transfer_app_config->pkt_header_size;

		if (transfer_app_data == NULL
			|| transfer_app_config->pkt_size <= 0)
		{
			LOGE("%s transfer_data: %p, size: %d\n", __func__, transfer_app_data, transfer_app_config->pkt_size);
			return BK_FAIL;
		}
	}
	else
	{
		if (transfer_app_data == NULL)
		{
			transfer_app_data = os_malloc(1472);
		}

		transfer_app_config->pkt_size = 1472 - transfer_app_config->pkt_header_size;
	}

	LOGI("%s transfer_data: %p, size: %d\n", __func__, transfer_app_data, transfer_app_config->pkt_size);
#else
bk_err_t transfer_app_task_init(video_setup_t *config)
{
	int ret = BK_OK;

	if (transfer_app_task_running)
	{
		LOGI("transfer_app_task already init!\r\n");
		return ret;
	}

	if (transfer_app_config == NULL)
	{
		transfer_app_config = (video_setup_t *)os_malloc(sizeof(video_setup_t));
		if (transfer_app_config == NULL)
		{
			LOGE("% malloc failed\r\n", __func__);
			return BK_ERR_NO_MEM;
		}
		os_memcpy(transfer_app_config, config, sizeof(video_setup_t));
	}

	if (transfer_app_data == NULL)
	{
		transfer_app_config->pkt_header_size = sizeof(transfer_data_t);
		if (transfer_app_config->send_type ==  TVIDEO_SND_UDP) {
			transfer_app_data = (transfer_data_t *)os_malloc(VIDEO_UDP_TRAN_LEN);
			transfer_app_config->pkt_size = VIDEO_UDP_TRAN_LEN - transfer_app_config->pkt_header_size;
		} else {
			transfer_app_data = (transfer_data_t *)os_malloc(VIDEO_TCP_TRAN_LEN);
			transfer_app_config->pkt_size = VIDEO_TCP_TRAN_LEN - transfer_app_config->pkt_header_size;
		}
		if (transfer_app_data == NULL)
		{
			LOGE("%s transfer_data malloc failed\n", __func__);
		}
	}

#endif

	if ((!transfer_app_task) && (!transfer_app_msg_que))
	{
		ret = rtos_init_queue(&transfer_app_msg_que,
								"transfer_app_msg_que",
								sizeof(trs_task_msg_t),
								20);
		if (BK_OK != ret)
		{
			LOGE("%s transfer_app_task init failed\n");
			ret = BK_ERR_NO_MEM;
			goto error;
		}

		ret = rtos_create_thread(&transfer_app_task,
								BEKEN_DEFAULT_WORKER_PRIORITY,
								"transfer_app_task",
								(beken_thread_function_t)transfer_app_task_entry,
								1536,
								NULL);

		if (BK_OK != ret)
		{
			LOGE("%s transfer_app_task init failed\n");
			ret = BK_ERR_NO_MEM;
			goto error;
		}
	}

	return ret;

error:

	if (transfer_app_msg_que)
	{
		rtos_deinit_queue(&transfer_app_msg_que);
		transfer_app_msg_que = NULL;
	}

	if (transfer_app_task)
	{
		transfer_app_task = NULL;
	}

	return ret;
}

static bk_err_t transfer_app_task_start_handle(media_mailbox_msg_t *mailbox_msg)
{
	if (transfer_app_task_running)
	{
		transfer_app_node = mailbox_msg;
		current_frame = (frame_buffer_t *)transfer_app_node->param;
		transfer_app_task_send_msg(TRS_TRANSFER_DATA, mailbox_msg->param);
	}
	else
	{
		LOGI("%s transfer_app_task not start\r\n", __func__);
		msg_send_rsp_to_media_app_mailbox(mailbox_msg, BK_OK);
	}

	return kNoErr;
}

static bk_err_t transfer_app_task_close_handle(media_mailbox_msg_t *mailbox_msg)
{
	if (transfer_app_task_running)
	{
		transfer_app_task_running = false;
		transfer_app_task_send_msg(TRS_TRANSFER_EXIT, mailbox_msg->param);
	}
	else
	{
		LOGI("%s transfer_app_task have closed\r\n", __func__);
	}

	return kNoErr;
}

bk_err_t transfer_app_event_handle(media_mailbox_msg_t *msg)
{
	int ret = kNoErr;

	switch (msg->event)
	{
		case EVENT_MEDIA_DATA_NOTIFY:
			ret = transfer_app_task_start_handle(msg);
			break;

		case EVENT_TRANSFER_CLOSE_IND:
			ret = transfer_app_task_close_handle(msg);
			break;

		default:
			break;
	}

	return ret;
}

