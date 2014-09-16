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
 
#ifndef READ_UID_H
#define READ_UID_H

#include <stdint.h>

/**
 @addtogroup
 @{
 */

/**
 Get a unique ID from the MCU. This is a 32-bit xor value created from the devices
 UUID or similar registers
 @param  storage for 128bits of UUID info
 @return none
*/
void read_uuid(uint32_t *uuid);

/**
 @}
 */

#endif
