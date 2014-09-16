/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "firmware_cfg.h"

fw_cfg_t const app = {
    .board_id   = "0200",
    .secret     = "00000000",
    .sector_size    = 0x400,
    // .sector_cnt = ((.flash_end - flash_start) / sector_size);
    .sector_cnt     = ((0x20000-0x0000)/0x400),
    .flash_start    = 0x0000,
    .flash_end      = 0x20000,
    .ram_start      = 0x1FFFE000,
    .ram_end        = 0x20002000
};
