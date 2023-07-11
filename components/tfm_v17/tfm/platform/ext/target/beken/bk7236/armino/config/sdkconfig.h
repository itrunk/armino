/*
 * Automatically generated file. DO NOT EDIT.
 * Beken IoT Development Framework (BEKEN-ARMINO) Configuration Header
 */
#pragma once

#define CONFIG_SOC_BK7236XX 1
#define CONFIG_SOC_BK7236 1
#define CONFIG_SOC_STR "bk7236"
#define CONFIG_SOC_ARCH "cm33"
#define CONFIG_TOOLCHAIN_PATH "/opt/gcc-arm-none-eabi-9-2020-q2-update/bin"
#define CONFIG_TOOLCHAIN_PREFIX "arm-none-eabi-"
#define CONFIG_CPU_FREQ_HZ 120000000
#define CONFIG_ASSERT_IGNORE 1
#define CONFIG_LWIP 1
#define CONFIG_LWIP_V2_1 1
#define CONFIG_NO_HOSTED 1
#define CONFIG_BLUETOOTH 1
#define CONFIG_ALI_MQTT 1
#define CONFIG_OTA_HTTP 1
#define CONFIG_AT_CMD 1
#define CONFIG_ATE 1
#define CONFIG_ATE_GPIO_ID 0
#define CONFIG_ATE_GPIO_PULL_UP 1
#define CONFIG_BLE 1
#define CONFIG_BLE_5_X 1
#define CONFIG_CLI 1
#define CONFIG_BKREG 1
#define CONFIG_MAX_COMMANDS 255
#define CONFIG_IPERF_TEST 1
#define CONFIG_EFUSE 1
#define CONFIG_ICU 0
#define CONFIG_COMPONENTS_WPA_TWT_TEST 1
#define CONFIG_MCU_PS 1
#define CONFIG_DEEP_PS 1
#define CONFIG_TICK_CALI 1
#define CONFIG_STA_PS 1
#define CONFIG_BK_NETIF 1
#define CONFIG_NON_OS 1
#define CONFIG_APP_MAIN_TASK_PRIO 4
#define CONFIG_APP_MAIN_TASK_STACK_SIZE 4096
#define CONFIG_BASE_MAC_FROM_RF_OTP_FLASH 1
#define CONFIG_RANDOM_MAC_ADDR 1
#define CONFIG_WIFI_ENABLE 1
#define CONFIG_WIFI6_CODE_STACK 1
#define CONFIG_WIFI6 1
#define CONFIG_WIFI4 1
#define CONFIG_MSDU_RESV_HEAD_LENGTH 96
#define CONFIG_MSDU_RESV_TAIL_LENGTH 16
#define CONFIG_TASK_RECONNECT_PRIO 4
#define CONFIG_WIFI6_IP_DEBUG 1
#define CONFIG_CMSIS 1
#define CONFIG_CAMERA_USE_I2C0 1
#define CONFIG_CAMERA_I2C_ID 0
#define CONFIG_DEMOS_IPERF 1
#define CONFIG_HTTP 1
#define CONFIG_DHCP 1
#define CONFIG_TASK_LWIP_PRIO 4
#define CONFIG_LWIP_MEM_REDUCE 1
#define CONFIG_TEMP_DETECT 1
#define CONFIG_INT_WDT 1
#define CONFIG_INT_WDT_PERIOD_MS 1000
#define CONFIG_TASK_WDT 1
#define CONFIG_TASK_WDT_PERIOD_MS 60000
#define CONFIG_UART1 1
#define CONFIG_UART2 1
#define CONFIG_PRINT_PORT_UART1 1
#define CONFIG_UART_PRINT_PORT 0
#define CONFIG_UART_ATE_PORT 1
#define CONFIG_PRINTF_BUF_SIZE 256
#define CONFIG_KFIFO_SIZE 128
#define CONFIG_TRNG_SUPPORT 1
#define CONFIG_SDIO_HOST 1
#define CONFIG_SDIO_HOST_DEFAULT_CLOCK_FREQ 200000
#define CONFIG_MAC_PHY_BYPASS 1
#define CONFIG_SPI_STATIS 1
#define CONFIG_SPI_SUPPORT_TX_FIFO_WR_READY 1
#define CONFIG_QSPI_STATIS 1
#define CONFIG_AON_RTC 1
#define CONFIG_GPIO_DYNAMIC_WAKEUP_SOURCE_MAX_CNT 4
#define CONFIG_GENERAL_DMA 1
#define CONFIG_JPEGENC_HW 1
#define CONFIG_CALENDAR 1
#define CONFIG_MPC 1
#define CONFIG_PRRO 1
#define CONFIG_XTAL_FREQ_26M 1
#define CONFIG_XTAL_FREQ 18750000
#define CONFIG_DCO_FREQ 120000000
#define CONFIG_SYSTEM_CTRL 1
#define CONFIG_I2C 1
#define CONFIG_I2C_SUPPORT_ID_BITS 1
#define CONFIG_FM_I2C 1
#define CONFIG_PWM 1
#define CONFIG_TIMER 1
#define CONFIG_TIMER_COUNTER 1
#define CONFIG_TIMER_SUPPORT_ID_BITS 0
#define CONFIG_SARADC 1
#define CONFIG_SARADC_NEED_FLUSH 1
#define CONFIG_FLASH 1

#ifdef CONFIG_TFM_NS
#define CONFIG_SPE 0
#else
#define CONFIG_SPE 1
#endif

#define CONFIG_TFM_NON_BOOTLOADER 1
#define CONFIG_BEKEN_SUPPORT_MPU 0
#define CONFIG_ENABLE_DEBUG 1
#define CONFIG_FPGA 1
#define CONFIG_ISR_REG_DISABLE 1
#define CONFIG_BK_PRINTF_DISABLE 1
#define CONFIG_STDIO_PRINTF 1
#define CONFIG_STDIO_PRINTF_BUF_SIZE 48
#define CONFIG_TFM_BL2_CRC 1
// eof

