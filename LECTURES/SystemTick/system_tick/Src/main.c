#include <stdio.h>
#include <stdint.h>
#include "stm32f107xx.h"
#include "systick.h"

#define GPIOAEN 	(1U<<2)
#define PIN5		(1U<<5)
#define LED5		PIN5
#define LED5_RESET	(1U<<21)

int main(void){

	//Enable clock acces for GPIOA
	RCC->APB2ENR |= GPIOAEN;

	//Set PA5 as output pin
	GPIOA->CRL &= ~(0xF<<20);
	GPIOA->CRL |= (0x1<<20); // 01: Output mode, max speed 10 MHz.

	while(1)
	{
		GPIOA->BSRR |= LED5;
		systickDelayMs(1000);
		GPIOA->BSRR |= LED5_RESET;
		systickDelayMs(1000);
	}
}
