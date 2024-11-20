#include "stm32f107xx.h"

#define GPIOAEN 	(0x1<<2)
#define GPIODEN 	(0x1<<5)
#define GPIOD0_HIGH	(0x1<<0)
#define LED0		(0x1<<0)
#define LED1		(0x1<<1)
#define LED4		(0x1<<4)
#define LED5		(0x1<<5)

void initClockHSI(void);
void delay(uint32_t time);
void initClockPLL(void);
void initClockHSE(void);

int main(void)
{
	// Initialize the clock to use PLL as the system clock
	initClockHSI();

	// RCC Configure for Port A and Port D
	RCC->APB2ENR |= GPIOAEN;
	RCC->APB2ENR |= GPIODEN;

	// Output Port Configuration for D0,D1,D4 and D5 pins
	GPIOD->CRL &= ~(0xF<<0);
	GPIOD->CRL |= (0x2<<0); // 10: Output mode, max speed 2 MHz.
	GPIOD->CRL &= ~(0xF<<4);
	GPIOD->CRL |= (0x2<<4); // 10: Output mode, max speed 2 MHz.
	GPIOD->CRL &= ~(0xF<<16);
	GPIOD->CRL |= (0x2<<16); // 10: Output mode, max speed 2 MHz.
	GPIOD->CRL &= ~(0xF<<20);
	GPIOD->CRL |= (0x2<<20); // 10: Output mode, max speed 2 MHz.

	// Configure Port A pin 3 as input
	GPIOA->CRL &= ~(0xF<<12);
	GPIOA->CRL |= (0x2<<14);

	// Set Pin D0 HIGH
	GPIOD->ODR |= GPIOD0_HIGH;

	while(1){
	// Check the state of pin 3 of Port A
	if ((GPIOA->IDR & (0x1<<3)) == (0x1<<3)) {
		if ((GPIOA->ODR & (0x1<<0)) == (0x1<<0)){
		GPIOD->ODR ^= LED0;
		GPIOD->ODR ^= LED1;
		delay(1454545);
		}
		else if ((GPIOD->ODR & (0x1<<1)) == (0x1<<1)){
		GPIOD->ODR ^= LED1;
		GPIOD->ODR ^= LED5;
		delay(1454545);
		}
		else if ((GPIOD->ODR & (0x1<<5)) == (0x1<<5)){
		GPIOD->ODR ^= LED5;
		GPIOD->ODR ^= LED4;
		delay(1454545);
		}
		else if ((GPIOD->ODR & (0x1<<4)) == (0x1<<4)){
		GPIOD->ODR ^= LED4;
		GPIOD->ODR ^= LED0;
		delay(1454545);
		}
	}
}
}

// Function to introduce a delay
void delay(uint32_t time) {
	    while (time--);
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
	while ((RCC->CR && (0x1<<25)) != 1); /*  PLL clock ready flag
	Set by hardware to indicate that the PLL is locked. */

	// Clear SW bits
	RCC->CFGR &= ~(0x3<<0);

	// Set PLL as the system clock
	RCC->CFGR |= (0x2<<0); //  10: PLL selected as system clock

	// Wait for PLL to be the system clock
	while((RCC->CFGR & (0x3<<2)) != (0x2<<2));
}

void initClockHSI(void) {
    RCC->CR |= RCC_CR_HSION; // Enable internal HSI (RC)
    while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY); // Wait for HSI to be ready

		//RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSI; // Set HSI as the system clock

    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for HSI to be the system clock
}

void initClockHSE(void) {
    RCC->CR |= RCC_CR_HSEON; // Enable external HSE (RC)
    while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY); // Wait for HSE to be ready

		//RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSE; // Set HSE as the system clock

    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE); // Wait for HSE to be the system clock
}
