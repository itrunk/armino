armino_build_get_property(target ARMINO_SOC)

set(incs
	soc/include
	hal/include
	)

set(srcs
	hal/timer_hal.c
	hal/dma_hal.c
	hal/icu_hal.c
	hal/wdt_hal.c
	hal/spi_hal.c
	hal/i2c_hal.c
	hal/gpio_hal.c
	hal/uart_hal.c
	hal/adc_hal.c
	)

if (CONFIG_AON_WDT)
	list(APPEND srcs
		hal/aon_wdt_hal.c
	)
endif()

if (CONFIG_PWM)
if (CONFIG_PWM_V1PX)
	list(APPEND srcs
		hal/pwm_hal_v1px.c
		)
endif()
if (CONFIG_PWM_V0P0)
	list(APPEND srcs
		hal/pwm_hal.c
		)
endif()
endif()

if (CONFIG_FLASH)
	list(APPEND srcs
		hal/flash_hal.c
	)
endif()

if (CONFIG_MPC)
	list(APPEND srcs
		hal/mpc_hal.c
	)
endif()

if (CONFIG_PRRO)
	list(APPEND srcs
		hal/prro_hal.c
	)
endif()

if (CONFIG_FFT)
	list(APPEND srcs
		hal/fft_hal.c
		)
endif()

if (CONFIG_I2S)
if (NOT CONFIG_SOC_BK7236XX)
	list(APPEND srcs
		hal/i2s_hal.c
		)
endif()
endif()

if(CONFIG_EFUSE)
	list(APPEND srcs
		hal/efuse_hal.c
	)
endif()

if(CONFIG_TRNG_SUPPORT)
	list(APPEND srcs
		"hal/trng_hal.c"
	)
endif()

if(CONFIG_MAILBOX)
	list(APPEND srcs
		"hal/mailbox_hal.c"
	)
endif()

if(CONFIG_QSPI)
	list(APPEND srcs
		"hal/qspi_hal.c"
	)
endif()

if(CONFIG_JPEGENC_HW)
	list(APPEND srcs
		"hal/jpeg_hal.c"
	)
endif()

if(CONFIG_YUV_BUF)
	list(APPEND srcs
		"hal/yuv_buf_hal.c"
	)
endif()

if(CONFIG_H264)
	list(APPEND srcs
		"hal/h264_hal.c"
	)
endif()

if(CONFIG_PSRAM)
	list(APPEND srcs
		"hal/psram_hal.c"
	)
endif()

if(CONFIG_AON_RTC)
	list(APPEND srcs
		"hal/aon_rtc_hal.c"
	)
endif()

if (CONFIG_SDIO_V2P0)
	list(APPEND srcs
		"hal/sdio_hal.c"
	)
endif()

if(CONFIG_VAULT_SUPPORT)
	list(APPEND srcs
		"hal/vault_hal.c"
	)
endif()

if(CONFIG_AUDIO)
if(CONFIG_SOC_BK7256XX)
	list(APPEND srcs
		"hal/aud_hal.c"
	)
endif()
if(CONFIG_SOC_BK7236XX)
	list(APPEND srcs
		"hal/aud_hal.c"
	)
endif()
endif()

if(CONFIG_SBC)
	list(APPEND srcs
		"hal/sbc_hal.c"
	)
endif()

if(CONFIG_CALENDAR)
	list(APPEND srcs
		"hal/calendar_hal.c"
	)
endif()

if(CONFIG_SDIO_HOST)
	list(APPEND srcs
		"hal/sdio_host_hal.c"
	)
endif()

if(CONFIG_SDMADC)
	list(APPEND srcs
		"hal/sdmadc_hal.c"
	)
endif()

if(CONFIG_OTP)
if (CONFIG_SOC_BK7236XX)
	list(APPEND srcs
		"hal/otp_hal.c"
	)
endif()
endif()

armino_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" REQUIRES ${target} tfm)
