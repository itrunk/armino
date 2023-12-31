// Copyright 2020-2021 Beken
//
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

#pragma once

#include <soc/soc.h>
#include "hal_port.h"
#include "wdt_hw.h"
#include <driver/hal/hal_wdt_types.h>
#include "sys_hal.h"
#include "aon_pmu_hal.h"

#ifdef __cplusplus
extern "C" {
#endif


#define WDT_LL_REG_BASE(_wdt_unit_id)    (SOC_AON_WDT_REG_BASE + _wdt_unit_id * 0x7ffa00)

static uint64_t wdt_exit_tick = 0;

static inline void wdt_ll_reset_config_to_default(wdt_hw_t *hw)
{
	hw->ctrl.key = 0;
	hw->ctrl.period = WDT_V_PERIOD_DEFAULT_VALUE;
}

static inline void wdt_ll_init(wdt_hw_t *hw)
{
	wdt_ll_reset_config_to_default(hw);
}

static inline void wdt_ll_set_1st_key(wdt_hw_t *hw)
{
	hw->ctrl.key = WDT_V_KEY_1ST;
}

static inline void wdt_ll_set_2nd_key(wdt_hw_t *hw)
{
	hw->ctrl.key = WDT_V_KEY_2ND;
}

static inline void wdt_ll_set_period(wdt_hw_t *hw, uint32_t period)
{
#if !CONFIG_DEBUG_FIRMWARE
	if (!aon_pmu_hal_is_chipid_later_than_version_C())
#endif
	{
		uint32_t nmi_wdt_clk_div = sys_hal_nmi_wdt_get_clk_div();
		uint32_t multi = 1;
		switch(nmi_wdt_clk_div) {
			case 0:    //wdt_clk = src_clk/2
				multi = 16;
				break;

			case 1:    //wdt_clk = src_clk/4
				multi = 8;
				break;

			case 2:    //wdt_clk = src_clk/8
				multi = 4;
				break;

			case 3:    //wdt_clk = src_clk/16
				multi = 2;
				break;

			default:
				multi = 1;
				break;
		}

		period = period * multi;
		if (period > WDT_F_PERIOD_M)
			period = WDT_F_PERIOD_M;
	}

	extern u64 riscv_get_mtimer(void);

	/*    NOTE: Wdt set two period need 3~4 clock(32K) interval.
	      In case of accidental set period fail, add 125us delay below for protection. */
	uint64_t tick_cnt = 125 * 26;	//125us
	while((riscv_get_mtimer() - wdt_exit_tick) < tick_cnt)
	{
		;
	}

	uint32_t ctrl_val = (period & WDT_F_PERIOD_M) | (WDT_V_KEY_1ST << WDT_F_KEY_S);
	hw->ctrl.v = ctrl_val;

	ctrl_val = (period & WDT_F_PERIOD_M) | (WDT_V_KEY_2ND << WDT_F_KEY_S);
	hw->ctrl.v = ctrl_val;
	wdt_exit_tick = riscv_get_mtimer();
}

#ifdef __cplusplus
}
#endif

