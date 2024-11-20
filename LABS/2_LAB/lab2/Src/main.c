#include "stm32f107xx.h"

#define GPIOAEN 	(0x1<<2)
#define GPIOCEN 	(0x1<<4)
#define LED4		(0x1<<4)
#define BIT_SET		(0x1<<13)
#define LED5		(0x1<<5)
#define BIT_RESET	(0x1<<29)

int main(void)
{
	//RCC Configuration
	RCC->APB2ENR |= GPIOAEN;
	RCC->APB2ENR |= GPIOCEN;
	//Port Configuration
	GPIOA->CRL &= ~(0xF<<16);
	GPIOA->CRL |= (0x2<<18); //PA4 Input with pull-up / pull-down
	GPIOA->CRL &= ~(0xF<<20);
	GPIOA->CRL |= (0x2<<22); //PA5 Input with pull-up / pull-down
	GPIOC->CRH &= ~(0xF<<20);
	GPIOC->CRH |= (0x2<<20); //PA13 Output mode, max speed 2 MHz.
	while(1){
	if(GPIOA->IDR & LED4){
	GPIOC->BSRR |= BIT_SET;
	}
	if(GPIOA->IDR & LED5){
	GPIOC->BSRR |= BIT_RESET;
	}
	}
}
