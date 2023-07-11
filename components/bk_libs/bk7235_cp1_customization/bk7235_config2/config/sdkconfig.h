/*
 * Automatically generated file. DO NOT EDIT.
 * Beken IoT Development Framework (BEKEN-ARMINO) Configuration Header
 */
#pragma once
#define CONFIG_SOC_BK7235 1
#define CONFIG_SOC_STR "bk7235_cp1"
#define CONFIG_SOC_ARCH "riscv"
#define CONFIG_SOC_BK7256XX 1
#define CONFIG_TOOLCHAIN_PATH "/opt/risc-v/nds32le-elf-mculib-v5f/bin"
#define CONFIG_TOOLCHAIN_PREFIX "riscv32-elf-"
#define CONFIG_ASSERT_REBOOT 1
#define CONFIG_NO_HOSTED 1
#define CONFIG_BLUETOOTH 1
#define CONFIG_AUDIO_AEC 1
#define CONFIG_AUDIO_RING_BUFF 1
#define CONFIG_AUDIO_G711 1
#define CONFIG_AUDIO_MP3 1
#define CONFIG_AUDIO_OPUS 1
#define CONFIG_DEVICE_MAX_NAME_LEN 32
#define CONFIG_INT_WDT_PERIOD_MS 1000
#define CONFIG_TASK_WDT 1
#define CONFIG_TASK_WDT_PERIOD_MS 60000
#define CONFIG_INT_AON_WDT_PERIOD_MS 1000
#define CONFIG_UART3 1
#define CONFIG_UART_PRINT_PORT 2
#define CONFIG_UART_ATE_PORT 1
#define CONFIG_PRINTF_BUF_SIZE 128
#define CONFIG_KFIFO_SIZE 128
#define CONFIG_SDIO_HOST_DEFAULT_CLOCK_FREQ 200000
#define CONFIG_SDCARD_DEFAULT_CLOCK_FREQ 9
#define CONFIG_SPI_DMA 1
#define CONFIG_SPI_SLAVE 1
#define CONFIG_SPI_MASTER 1
#define CONFIG_SPI_STATIS 1
#define CONFIG_SPI_SUPPORT_TX_FIFO_WR_READY 1
#define CONFIG_QSPI_STATIS 1
#define CONFIG_GPIO_DYNAMIC_WAKEUP_SOURCE_MAX_CNT 4
#define CONFIG_CONFIG_GPIO_WAKEUP_ID 22
#define CONFIG_CONFIG_GPIO_WAKEUP_INT_TYPE 0
#define CONFIG_CHANGE_JTAG_GPIO 1
#define CONFIG_AON_PMU 1
#define CONFIG_GENERAL_DMA 1
#define CONFIG_SBC 1
#define CONFIG_JPEGENC_HW 1
#define CONFIG_PSRAM 1
#define CONFIG_XTAL_FREQ_26M 1
#define CONFIG_XTAL_FREQ 26000000
#define CONFIG_DCO_FREQ 120000000
#define CONFIG_SYSTEM_CTRL 1
#define CONFIG_DEFAULT_LPO_SRC 2
#define CONFIG_I2C 1
#define CONFIG_I2C_SUPPORT_ID_BITS 1
#define CONFIG_AUDIO 1
#define CONFIG_AUDIO_RISCV_IP_V1_0 1
#define CONFIG_TIMER 1
#define CONFIG_TIMER_SUPPORT_ID_BITS 0
#define CONFIG_RESET_REASON 1
#define CONFIG_MAILBOX 1
#define CONFIG_CPU_FREQ_HZ 120000000
#define CONFIG_ARCH_RISCV 1
#define CONFIG_MEMDUMP_ALL 1
#define CONFIG_WIFI6_CODE_STACK 1
#define CONFIG_WIFI4 1
#define CONFIG_WIFI6 1
#define CONFIG_MSDU_RESV_HEAD_LENGTH 96
#define CONFIG_MSDU_RESV_TAIL_LENGTH 16
#define CONFIG_TASK_RECONNECT_PRIO 4
#define CONFIG_CLI 1
#define CONFIG_MAX_COMMANDS 255
#define CONFIG_SHELL_ASYNCLOG 1
#define CONFIG_SBC_TEST 1
#define CONFIG_DUAL_CORE 1
#define CONFIG_SLAVE_CORE 1
#define CONFIG_CUSTOMIZE_HEAP_SIZE 163840
#define CONFIG_FREERTOS 1
#define CONFIG_FREERTOS_V10 1
#define CONFIG_FREERTOS_USE_TICKLESS_IDLE 2
#define CONFIG_MQTT_ACK_NOW 1
#define CONFIG_HOMEKIT 1
#define CONFIG_WIFI_IP_AX 1
#define CONFIG_WIFI_MAC_VERSION "V21"
#define CONFIG_WIFI_MDM_VERSION "v30"
#define CONFIG_WIFI_PLF_VERSION "v31"
#define CONFIG_MM_PS_SET_LISTEN_INTERVAL_VALUE 30
#define CONFIG_MM_BEACON_LOSS_INITAL_COEFF 4
#define CONFIG_MM_BEACON_LOSS_LOW_COEFF 8
#define CONFIG_MM_BEACON_LOSS_MIDDLE_COEFF 20
#define CONFIG_MM_BEACON_LOSS_HIGH_COEFF 40
#define CONFIG_MM_BEACON_LOSS_RSSI_THRESHOLD -80
#define CONFIG_MAC_RESET_BCMC_AUTO_MODE 1
#define CONFIG_MAC_KEEP_ALIVE_PERIOD_AUTO_MODE 1
#define CONFIG_DHCP_PROTECT_IN_CONNECTED 1
#define CONFIG_TCP_PROTECT_IN_CONNECTED 1
#define CONFIG_BK_MEMORY_CUT_EN 1
#define CONFIG_NX_HW_PARSER_TIM_ELEMENT 1
#define CONFIG_MAC_SUPPORT_DYNAMIC_CPU_FREQ 1
#define CONFIG_MAC_PM_ROSC_CALI 1
#define CONFIG_NX_MEDIA_DYNC_DTIM 1
#define CONFIG_PER_PACKET_INFO_OUTPUT 1
#define CONFIG_BK_MEM_DYNA_APPLY_EN 1
#define CONFIG_NX_OTA_DYNC_DTIM 1
#define CONFIG_MAC_SFRAME_SOFTWARE_RETRY 1
#define CONFIG_SM_FAST_CONNECT 1
#define CONFIG_LV_COLOR_DEPTH 16
#define CONFIG_MSDU_RESV_HEAD_LEN 96
#define CONFIG_MSDU_RESV_TAIL_LEN 16
#define CONFIG_USB 1
#define CONFIG_USB_HOST 1
#define CONFIG_USB2_PORT 1
#define CONFIG_TASK_USB_PRIO 5
#define CONFIG_USB_UVC 1
#define CONFIG_DSP_SRC_ADD 0x130000
#define CONFIG_VIDEO_SCALE 1
#define CONFIG_FAST_CONNECT_INFO_ENC_METHOD 1
#define CONFIG_WPA_AUTH_TIMEOUT 2
