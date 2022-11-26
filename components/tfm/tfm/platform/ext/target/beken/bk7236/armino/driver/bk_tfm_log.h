// Copyright 2022-2023 Beken
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

#include "components/log.h"

#if CONFIG_BK_TFM_DUMP_BUF
void bk_tfm_dump_buf(const char *str, const uint8_t *buf, uint32_t len);
#define BK_TFM_DUMP_BUF(prompt, buf, len) bk_tfm_dump_buf((prompt), (buf), (len))
#else
#define BK_TFM_DUMP_BUF(prompt, buf, len)
#endif

