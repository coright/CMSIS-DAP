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
 
#include "flash_erase_read_write.h"
#include "firmware_cfg.h"
#include "flash_algo.h"

uint32_t dnd_flash_init(uint32_t clk)
{
    // from flash_algo.c, 1 is failing and 0 is passing
    return (Init(0, 0, 0)) ? 0 : 1;
}

uint32_t dnd_flash_uninit(void)
{
    // from flash_algo.c, 1 is failing and 0 is passing
    return (UnInit(0)) ? 0 : 1;
}

uint32_t __SVC_2 (uint32_t num) 
{
    uint32_t res = 0;
    NVIC_DisableIRQ(USB0_IRQn);
    res = EraseSector(num * app.sector_size);
    NVIC_EnableIRQ(USB0_IRQn);
    // from flash_algo.c, 1 is failing and 0 is passing
    return !res;
}

uint32_t dnd_erase_sector(uint32_t num)
{
    return erase_sector_svc(num);
}

uint32_t dnd_erase_chip(void)
{
    uint32_t i = app.flash_start;
    // dont erase the bootloader, just the app region 
    for( ; i < app.flash_end; i += app.sector_size) {
        if (!erase_sector_svc(i / app.sector_size)) {
            return 0;
        }
    }
    return 1;
}

uint32_t __SVC_3 (uint32_t adr, uint8_t * buf, uint32_t size)
{
    uint32_t res = 0;
    NVIC_DisableIRQ(USB0_IRQn);
    res = ProgramPage(adr, size, buf);
    NVIC_EnableIRQ(USB0_IRQn);
    // from flash_algo.c, 1 is failing and 0 is passing 
    return !res;
}

uint32_t dnd_program_page(uint32_t adr, uint8_t * buf, uint32_t size)
{
    return program_page_svc(adr, buf, size);
}

uint32_t dnd_read_memory(uint32_t adr, uint8_t *buf, uint32_t size)
{
	uint8_t *start_address = (uint8_t *)adr;
    while(size--) {
        *buf++ = *(uint8_t *)adr++;
    }
    return adr - *(uint8_t *)start_address;
}
