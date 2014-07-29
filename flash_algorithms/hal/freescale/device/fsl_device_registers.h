/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

// Note: includes commented out to speed up compilation of flash algo.

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || \
    defined(CPU_MK20DN64VMP5) || defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || \
    defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || defined(CPU_MK20DX64VLH5) || \
    defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || \
    defined(CPU_MK20DN64VFM5) || defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || \
    defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || defined(CPU_MK20DX64VFT5) || \
    defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || \
    defined(CPU_MK20DN64VLF5) || defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK20D5_fmc.h"
    #include "MK20D5_ftfl.h"
    #include "MK20D5_sim.h"

    // CMSIS-style register definitions
    #include "MK20D5.h"

#elif (defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || \
    defined(CPU_MK22FN256VMP12))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK22F25612_fmc.h"
    #include "MK22F25612_ftfa.h"
    #include "MK22F25612_mcm.h"
    #include "MK22F25612_sim.h"

    // CMSIS-style register definitions
    #include "MK22F25612.h"

#elif (defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK22F51212_fmc.h"
    #include "MK22F51212_ftfa.h"
    #include "MK22F51212_mcm.h"
    #include "MK22F51212_sim.h"

    // CMSIS-style register definitions
    #include "MK22F51212.h"

#elif (defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLQ12))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK24F12_fmc.h"
    #include "MK24F12_ftfe.h"
    #include "MK24F12_mcm.h"
    #include "MK24F12_sim.h"

    // CMSIS-style register definitions
    #include "MK24F12.h"

#elif (defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK63F12_fmc.h"
    #include "MK63F12_ftfe.h"
    #include "MK63F12_mcm.h"
    #include "MK63F12_sim.h"

    // CMSIS-style register definitions
    #include "MK63F12.h"

#elif (defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VMD12) || defined(CPU_MK64FX512VMD12))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK64F12_fmc.h"
    #include "MK64F12_ftfe.h"
    #include "MK64F12_mcm.h"
    #include "MK64F12_sim.h"

    // CMSIS-style register definitions
    #include "MK64F12.h"

#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK70F12_fmc.h"
    #include "MK70F12_ftfe.h"
    #include "MK70F12_mcm.h"
    #include "MK70F12_sim.h"

    // CMSIS-style register definitions
    #include "MK70F12.h"

#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MK70F15_fmc.h"
    #include "MK70F15_ftfe.h"
    #include "MK70F15_mcm.h"
    #include "MK70F15_sim.h"

    // CMSIS-style register definitions
    #include "MK70F15.h"

#elif (defined(CPU_MKL02Z32VFM4) || defined(CPU_MKL02Z16VFM4) || defined(CPU_MKL02Z16VFK4) || defined(CPU_MKL02Z32VFK4) || defined(CPU_MKL02Z8VFG4) || defined(CPU_MKL02Z16VFG4) || defined(CPU_MKL02Z32VFG4) || defined(CPU_MKL02Z32CAF4))

    #include "MKL02Z4_ftfa.h"
    #include "MKL02Z4_mcm.h"
    #include "MKL02Z4_sim.h"

    // CMSIS-style register definitions
    #include "MKL02Z4.h"

#elif (defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || \
    defined(CPU_MKL05Z8VLC4) || defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || \
    defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || defined(CPU_MKL05Z32VFM4) || \
    defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MKL05Z4_ftfa.h"
    #include "MKL05Z4_mcm.h"
    #include "MKL05Z4_sim.h"

    // CMSIS-style register definitions
    #include "MKL05Z4.h"

#elif (defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || \
    defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || \
    defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MKL25Z4_ftfa.h"
    #include "MKL25Z4_mcm.h"
    #include "MKL25Z4_sim.h"

    // CMSIS-style register definitions
    #include "MKL25Z4.h"

#elif (defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4))
    // Extension register headers. (These will eventually be merged into the CMSIS-style header.)
    #include "MKL46Z4_ftfa.h"
    #include "MKL46Z4_mcm.h"
    #include "MKL46Z4_sim.h"

    // CMSIS-style register definitions
    #include "MKL46Z4.h"

#else
    #error "No valid CPU defined!"
#endif

#endif // __FSL_DEVICE_REGISTERS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
