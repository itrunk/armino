set(incs ble_boarding)
set(srcs)

if (CONFIG_AT_CMD)
if (NOT CONFIG_BTDM_CONTROLLER_ONLY)
	list(APPEND srcs
		ble_boarding/ble_boarding.c
		ble_boarding/dm_ble_boarding.c
		)
endif()
endif()

if (CONFIG_A2DP_SINK_DEMO)
	list(APPEND srcs
		a2dp_sink/a2dp_sink_demo.c
		a2dp_sink/ring_buffer_node.c
		)
endif()

if (CONFIG_A2DP_SOURCE_DEMO)

endif()

if (CONFIG_HFP_HF_DEMO)
	list(APPEND srcs
		hfp_hf/hfp_hf_demo.c
		)
endif()

armino_component_register(SRCS "${srcs}"
	INCLUDE_DIRS "${incs}"
	PRIV_REQUIRES bk_common at aac_decoder
	)
