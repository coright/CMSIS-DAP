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
 
#include <sam3u.h>
#include <RTL.h>
#include <debug_cm.h>
#include "target_reset.h"
#include "swd_host.h"
#include "gpio.h"

//Blink with 50ms interval
static void blinkLED(){
    gpio_set_dap_led(1);
    os_dly_wait(5);
    gpio_set_dap_led(0);
    os_dly_wait(5);
    gpio_set_dap_led(1);
}
//Erase NRF and blink every 50ms in the process
static void nrf_Emergency_Erase(){
    //make sure SWD is initialized
    swd_init_debug();    
    
    blinkLED();    
    
    //Set NVMC->CONFIG on NRF to 2    
    swd_write_ap(AP_TAR, 0x4001E000 + 0x504);
    swd_write_ap(AP_DRW, 2);

    blinkLED();
    blinkLED();
   

    //Set NVMC->ERASEALL on NRF to 1 to start chip erase
    swd_write_ap(AP_TAR, 0x4001E000 + 0x50C);
    swd_write_ap(AP_DRW, 1);
    
    blinkLED();
    blinkLED();
    blinkLED();
    blinkLED();
    
    //Set NVMC->CONFIG on NRF to 0
    swd_write_ap(AP_TAR, 0x4001E000 + 0x504);
    swd_write_ap(AP_DRW, 0);
    
    blinkLED();
    blinkLED();
}

void target_before_init_debug(void) {
    return;
}

uint8_t target_unlock_sequence(void) {
    return 1;
}

uint8_t target_set_state(TARGET_RESET_STATE state) {
	uint32_t  count=0;
	//Check for 5 Second emergency erase routine
	while(!((PIOA->PIO_PDSR >> 25) &1)){
        os_dly_wait(1);
        count++;
        gpio_set_dap_led((count>>4)&1);//Blink every 160ms
        if(count>500){            
            nrf_Emergency_Erase();
            return swd_set_target_state(state);
        }
    }
    gpio_set_dap_led(1);
    return swd_set_target_state(state);
}
