#include "stm32f107xx.h"

void initClockPLL(void);

int main(void){
	initClockPLL();
}

void initClockPLL(void){

	// Set HSI as the system clock
	RCC->CFGR &= ~(0x3 << 0);  // Clear bits 1:0, setting SW to 00 (HSI as system clock)

	// Wait for HSI to be the system clock
	while ((RCC->CFGR & (0x3 << 2)) != 0x0);  // Check the SWS bits in RCC_CFGR

	// Disable the PLL
	RCC->CR &= ~(0x1<<24); // 0: PLL OF
	while ((RCC->CR & (0x1 << 25)) != 0x0);

	// Set HSI/2 as PLL entry clock source
	RCC->CFGR &= ~(0x1<<16); //  0: HSI oscillator clock / 2 selected as PLL input clock

	// Set PLL multiplication factor
	RCC->CFGR &= ~(0xF<<18); // Clear PLL Multiplication factor bits
	RCC->CFGR |= (0xC<<18); //  PLL input clock x 14

	// Enable PLL (RC)
	RCC->CR |= (0x1<<24); // 1: PLL ON

	// Wait for PLL to be ready
	while ((RCC->CR & (0x1<<25)) != 1); /*  PLL clock ready flag
	Set by hardware to indicate that the PLL is locked. */

	// Clear SW bits
	RCC->CFGR &= ~(0x3<<0);

	// Set PLL as the system clock
	RCC->CFGR |= (0x2<<0); //  10: PLL selected as system clock

	// Wait for PLL to be the system clock
	while((RCC->CFGR & (0x3<<2)) != (0x2<<2));
}
