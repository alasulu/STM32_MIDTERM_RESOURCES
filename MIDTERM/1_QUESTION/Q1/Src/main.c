#include "stm32f107xx.h"

#define GPIOBEN 	(0x1<<3)
#define GPIOB5EN	(0x1<<5)
#define LED5		(GPIOB5EN)
#define GPIOB3EN	(0x1<<3)
#define LED3		(GPIOB3EN)
#define LED7		(1U<<7)
#define BIT_SET		(0x1<<5)
#define BIT_RESET	(0x1<<21)


int main(){
	/* QUESTION 1
	 * STM32F107 has a GPIO ports with multiple pins that can be configured as either
inputs or outputs. If a program wants to use GPIO port B pin 5 as an output, but also
wants to read the status of another input connected to GPIO port B pin 7, write
configuration code snippet in C. (30 pts)
	 */

	// Enable port B clock
	RCC->APB2ENR |= GPIOBEN;

	// Configure Port B pins 5 as an output
	GPIOB->CRL &= ~(0xF<<20);
	GPIOB->CRL |= (0x2<<20); // Output mode, max speed 2 MHz for PB5.

	// Configure Port B pin 7 as an input
	GPIOC->CRL &= ~(0xF<<28);
	GPIOC->CRL |= (0x2<<30); // Input with pull-up / pull-down for PB7.

	/* !!!!Extra (Led ON at PB5 when PB3 pushed)!!!! */
	GPIOB->CRL &= ~(0xF<<12);
	GPIOB->CRL |= (0x2<<14); // Input with pull-up / pull-down for PB3

	while(1){
	if(GPIOC->IDR & LED3){
		GPIOB->BSRR |= BIT_SET;
	}
	if((GPIOC->IDR & LED3) == 0){
		GPIOB->BSRR |= BIT_RESET;
		}
	}
	}

