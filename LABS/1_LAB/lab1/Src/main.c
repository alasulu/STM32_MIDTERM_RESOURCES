#include "stm32f107xx.h"

#define GPIOCEN 	(0x1<<4)
#define LEDPINC13	(0x1<<13)
#define PIN13		(LEDPINC13)

int main(void)
{
	//RCC Configuration
	RCC->APB2ENR |= GPIOCEN;
	//Port Configuration
	GPIOC->CRH &= ~(0xF<<20);
	GPIOC->CRH |= (0x2<<20);  //10: Output mode, max speed 2 MHz.
while(1){
	// 3. LED Blinking
	GPIOC->ODR ^= PIN13;
	// 4. Simple delay loop
	for (int i = 0; i < 2000000; i++) {}
}
}
