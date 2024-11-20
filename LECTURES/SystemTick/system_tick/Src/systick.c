#include "stm32f107xx.h"

#define SYSTICK_LOAD_VAL 	(9000)
#define CTRL_CONFIGURATION	(0x5<<0)
#define CTRL_COUNTERFLAG	(0x1<<16)

void systickDelayMs(int delay){
// We create a function that's not going to somewhere else but if only if
// turning back an integer n value

	//--Configure the Systick--//

	//Reloads with number of clock per millisecond//
	SysTick->LOAD |= SYSTICK_LOAD_VAL;

	//Clear Systick Current Value Register//
	//Enable Systick and select internal clock source//
	SysTick->VAL  |= 0;
	SysTick->CTRL |= CTRL_CONFIGURATION; /*  1 = counter enabled (0th bit).
	1 = processor clock (3rd bit) */

	for(int i=0;i<delay;i++){
		 // Wait until count flag is set
		while ((SysTick->CTRL & CTRL_COUNTERFLAG) == 0); /* COUNTFLAG Returns
		1 if timer counted to 0 since last time this was read. */
	}

	SysTick->CTRL = 0;

}
