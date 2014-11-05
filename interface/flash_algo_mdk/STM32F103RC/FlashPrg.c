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

#include "../FlashOS.H"        // FlashOS Structures

#define U8  unsigned char
#define U16 unsigned short
#define U32 unsigned long
#define U64 unsigned long long

#define I8  signed char
#define I16 signed short
#define I32 signed long


/*********************************************************************
*
*       Register definitions
*/
#define FLASH_ACR_REG        (*(volatile unsigned long *)0x40022000)
#define FLASH_KEYR_REG       (*(volatile unsigned long *)0x40022004)
#define FLASH_OPTKEYR_REG    (*(volatile unsigned long *)0x40022008)
#define FLASH_SR_REG         (*(volatile unsigned long *)0x4002200C)
#define FLASH_CR_REG         (*(volatile unsigned long *)0x40022010)
#define FLASH_AR_REG         (*(volatile unsigned long *)0x40022014)
#define FLASH_OBR_REG        (*(volatile unsigned long *)0x4002201C)
#define FLASH_WRPR_REG       (*(volatile unsigned long *)0x40022020)
	

/*********************************************************************
*
*      SR Register bit definitions
*/
#define FLASH_SR_BSY          0x01
#define FLASH_SR_PGERR        0x04
#define FLASH_SR_WRPRTERR     0x10
#define FLASH_SR_EOP          0x20

/*********************************************************************
*
*      CR Register bit definitions
*/
#define FLASH_CR_PG          0x01
#define FLASH_CR_PER         0x02
#define FLASH_CR_MER         0x04
#define FLASH_CR_STRT        0x40
#define FLASH_CR_LOCK        0x80


/*********************************************************************
*
*      FLASH key
*/
#define FLASH_RDPRT_KEY        0x00A5
#define FLASH_UNLOCK_KEY1      0x45670123
#define FLASH_UNLOCK_KEY2      0xCDEF89AB



	

/*
 *  Unlock the flash
 *    Parameter:      None
 *    Return Value:   0 - OK,  
 */
 int UnlockFlash(void) {
    FLASH_KEYR_REG = FLASH_UNLOCK_KEY1;
    FLASH_KEYR_REG = FLASH_UNLOCK_KEY2;
    return 0;
 }



/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
int Init (unsigned long adr, unsigned long clk, unsigned long fnc) {
	//
	// No special init necessary
	//
	/*clear SR*/
	FLASH_SR_REG = FLASH_SR_PGERR | FLASH_SR_WRPRTERR | FLASH_SR_EOP;
  return (0);
}

/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit (unsigned long fnc) {
	//
	// No special uninit necessary
	//
  return (0);
}

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */
int EraseChip (void) {

	U32 cr = 0;
	U32 sr = 0;
	
	/*check flash is locked, if yes, unlock it*/
	cr = FLASH_CR_REG;
	if( (cr & FLASH_CR_LOCK) == FLASH_CR_LOCK)
	{
		UnlockFlash();
	}
	/*wait SR BSY cleared*/
	do{
		sr = FLASH_SR_REG;
	}while((sr & FLASH_SR_BSY) == FLASH_SR_BSY);
	
	/*first set MER bit, then set STRT bit*/
	cr = FLASH_CR_REG;
	cr |= FLASH_CR_MER;
	FLASH_CR_REG = cr;
	
	cr = FLASH_CR_REG;
	cr |= FLASH_CR_STRT;
	FLASH_CR_REG = cr;	
	
	/*wait SR BSY cleared*/
	do{
		sr = FLASH_SR_REG;
	}while((sr & FLASH_SR_BSY) == FLASH_SR_BSY);

	/*clear MER bit*/
	cr = FLASH_CR_REG;
	cr &= ~FLASH_CR_MER;
	FLASH_CR_REG = cr;
	

  return (0);                                    // Finished without Errors
}

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */
int EraseSector (unsigned long adr) {
	U32 cr = 0;
	U32 sr = 0;
	/*check flash is locked, if yes, unlock it*/
	cr = FLASH_CR_REG;
	if( (cr & FLASH_CR_LOCK) == FLASH_CR_LOCK)
	{
		UnlockFlash();
	}
	/*wait SR BSY cleared*/
	do{
		sr = FLASH_SR_REG;
	}while((sr & FLASH_SR_BSY) == FLASH_SR_BSY);	
	
	/*first set PER bit, then set address, last set STRT bit*/
	cr = FLASH_CR_REG;
	cr |= FLASH_CR_PER;
	FLASH_CR_REG = cr;
	
	/*set erase sector address*/
	FLASH_AR_REG = adr; 
	
	cr = FLASH_CR_REG;
	cr |= FLASH_CR_STRT;
	FLASH_CR_REG = cr;	
	
	/*wait SR BSY cleared*/
	do{
		sr = FLASH_SR_REG;
	}while((sr & FLASH_SR_BSY) == FLASH_SR_BSY);

	/*clear PER bit*/
	cr = FLASH_CR_REG;
	cr &= ~FLASH_CR_PER;
	FLASH_CR_REG = cr;	

  return (0);
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */
int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {
  volatile U16* pDest;
  volatile U16* pSrc;
  U32 NumWords;
  U32 Status;
	U32 cr = 0;
	U32 sr = 0;
	unsigned long i = 0;
	U16 data;
	
  pDest = (volatile U16*)adr;
  pSrc = (volatile U16*)buf;    // Always 32-bit aligned. Made sure by CMSIS-DAP firmware
	//
	// adr is always aligned to "Programming Page Size" specified in table in FlashDev.c
  // sz is always a multiple of "Programming Page Size"
	//
	/*check flash is locked, if yes, unlock it*/
	cr = FLASH_CR_REG;
	if( (cr & FLASH_CR_LOCK) == FLASH_CR_LOCK)
	{
		UnlockFlash();
	}
	/*wait SR BSY cleared*/
	do{
		sr = FLASH_SR_REG;
	}while((sr & FLASH_SR_BSY) == FLASH_SR_BSY);	

	while(i < sz/2 )
	{
		/*first set PG bit in CR, then write data to flash address*/
		cr = FLASH_CR_REG;
		cr |= FLASH_CR_PG;
		FLASH_CR_REG = cr;
		
		*pDest = *pSrc;
		/*wait SR BSY cleared*/
		do{
			sr = FLASH_SR_REG;
		}while((sr & FLASH_SR_BSY) == FLASH_SR_BSY);
		
		/*check program word is ok*/
		if(*pSrc != *pDest)
		{
			/*clear PG bit*/
			cr = FLASH_CR_REG;
			cr &= ~FLASH_CR_PG;
			FLASH_CR_REG = cr;	
			
			return 1;
		}
		pDest++;
		pSrc++;
		i++;	
	}
	
	/*clear PG bit*/
	cr = FLASH_CR_REG;
	cr &= ~FLASH_CR_PG;
	FLASH_CR_REG = cr;		
	
  return (0);                                  // Finished without Errors
}
