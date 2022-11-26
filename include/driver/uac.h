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
//
#pragma once
#include <common/bk_include.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @brief Overview about this API header
 *
 */

/**
 * @brief AUD API
 * @defgroup bk_api_aud AUD API group
 * @{
 */

bk_err_t bk_aud_uac_driver_init(void);
bk_err_t bk_aud_uac_driver_deinit(void);
bk_err_t bk_aud_uac_start_mic(void);
bk_err_t bk_aud_uac_stop_mic(void);
bk_err_t bk_aud_uac_start_spk(void);
bk_err_t bk_aud_uac_stop_spk(void);
bk_err_t bk_aud_uac_register_mic_callback(void *cb);
bk_err_t bk_aud_uac_unregister_mic_callback(void);
bk_err_t bk_aud_uac_register_spk_buff_ptr(void *buff, uint32_t size);
bk_err_t bk_aud_uac_register_spk_callback(void *cb);
bk_err_t bk_aud_uac_unregister_spk_callback(void);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif
