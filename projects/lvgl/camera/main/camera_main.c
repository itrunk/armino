#include "bk_private/legacy_init.h"
#include <components/system.h>
#include <os/os.h>
#include <components/shell_task.h>

#include "cli.h"

#include "lcd_act.h"
#include "media_app.h"
#include "lv_vendor.h"
#include "driver/drv_tp.h"

extern void user_app_main(void);
extern void rtos_set_user_app_entry(beken_thread_function_t entry);

#define CMDS_COUNT  (sizeof(s_lvcamera_commands) / sizeof(struct cli_command))


extern void lv_example_meter(void);
extern void lv_example_meter_exit(void);

#define CAMERA_PPI PPI_800X480

const lcd_open_t lcd_open =
{
	//.device_ppi = PPI_800X480,
	//.device_name = "h050iwv",
	.device_ppi = PPI_480X800,
	.device_name = "st7710s",
};


void lvcamera_open(void)
{
	os_printf("%s\r\n", __func__);

#if (CONFIG_TP)
	drv_tp_close();
#endif
	lv_example_meter_exit();
	lv_vendor_stop();
	media_app_camera_open(APP_CAMERA_UVC, CAMERA_PPI);
}

void lvcamera_close(void)
{
	os_printf("%s\r\n", __func__);

	media_app_camera_close(APP_CAMERA_UVC);

#if (CONFIG_TP)
	drv_tp_open(ppi_to_pixel_x(lcd_open.device_ppi), ppi_to_pixel_y(lcd_open.device_ppi));
#endif

	lv_vendor_start();
	lv_example_meter();
}


void cli_lvcamera_cmd(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
	os_printf("%s\r\n", __func__);

	if (os_strcmp(argv[1], "open") == 0)
	{
		lvcamera_open();
	}

	if (os_strcmp(argv[1], "close") == 0)
	{
		lvcamera_close();
	}

}

static const struct cli_command s_lvcamera_commands[] =
{
	{"lvcam", "lvcam", cli_lvcamera_cmd},
};

int cli_lvcamera_init(void)
{
	os_printf("%s\r\n", __func__);
	return cli_register_commands(s_lvcamera_commands, CMDS_COUNT);
}


#ifdef CONFIG_CACHE_CUSTOM_SRAM_MAPPING
const unsigned int g_sram_addr_map[4] =
{
	0x38000000,
	0x30020000,
	0x38020000,
	0x30000000
};
#endif

void lvcamera_main_init(void)
{
	bk_err_t ret;
	lv_vnd_config_t lv_vnd_config;

	os_printf("meter Start\r\n");

	cli_lvcamera_init();

#ifdef CONFIG_LVGL_USE_PSRAM
#define PSRAM_DRAW_BUFFER ((0x60000000UL) + 5 * 1024 * 1024)

	lv_vnd_config.draw_pixel_size = ppi_to_pixel_x(lcd_open.device_ppi) * ppi_to_pixel_y(lcd_open.device_ppi);
	lv_vnd_config.draw_buf_2_1 = (lv_color_t *)PSRAM_DRAW_BUFFER;
	lv_vnd_config.draw_buf_2_2 = (lv_color_t *)(PSRAM_DRAW_BUFFER + lv_vnd_config.draw_pixel_size * sizeof(lv_color_t));
#else
	lv_vnd_config.draw_pixel_size = (30 * 1024) / sizeof(lv_color_t);
	lv_vnd_config.draw_buf_2_1 = LV_MEM_CUSTOM_ALLOC(lv_vnd_config.draw_pixel_size * sizeof(lv_color_t));
	lv_vnd_config.draw_buf_2_2 = NULL;
#endif
	lv_vnd_config.rotation = ROTATE_NONE;

#if (CONFIG_TP)
	drv_tp_open(ppi_to_pixel_x(lcd_open.device_ppi), ppi_to_pixel_y(lcd_open.device_ppi));
#endif

	lv_vendor_init(&lv_vnd_config, ppi_to_pixel_x(lcd_open.device_ppi), ppi_to_pixel_y(lcd_open.device_ppi));
	media_app_lcd_rotate(BK_TRUE);
	ret = media_app_lcd_open((lcd_open_t *)&lcd_open);
	lv_vendor_start();

	if (ret != BK_OK)
	{
		os_printf("media_app_lcd_open failed\r\n");
	}

	lv_example_meter();
}

void user_app_main(void)
{
}

int main(void)
{
#if (!CONFIG_SLAVE_CORE)
	rtos_set_user_app_entry((beken_thread_function_t)user_app_main);
	// bk_set_printf_sync(true);
	// shell_set_log_level(BK_LOG_WARN);
#endif
	legacy_init();

#ifdef CONFIG_LV_USE_DEMO_METER
	lvcamera_main_init();
#endif

	return 0;
}