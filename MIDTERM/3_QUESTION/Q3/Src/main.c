#include <stdio.h>
#include <stdint.h>
#include "stm32f107xx.h"

#define GPIOAEN 	(1U<<2)
#define AFIOEN	(1U<<0)
#define LINE0             (0x1 << 0)
#define LINE2             (0x1 << 2)
#define PINC13            (0x1 << 13)
#define LEDC13            (PINC13)
#define LEDC13_R          (0x1 << 29)
#define DEBOUNCE_DELAY_MS 1000

void SysTick_Handler(void);
void systick_init(void);
static void exti0_callback(void);
void EXTI0_IRQHandler(void);

volatile uint32_t ms_ticks = 0;           // Millisecond counter
volatile uint32_t last_interrupt_time = 0; // Last interrupt time in ms


int main(void){
	// Initialize the clock to use PLL as the system clock

	//initClockHSI()

	// RCC Configuration for PORTA
	RCC->APB2ENR |= GPIOAEN;

	//Set PA2 as input pin
	GPIOA->CRL &= ~(0xF<<8);
	GPIOA->CRL |= (0x2<<10); // 10: Input with pull-up / pull-down

	// Enable the AFIO clock
	RCC->APB2ENR |= AFIOEN;

	// Connect EXTI2 to GPIOA pin 2 (EXTI0 cannot be connected to GPIOA pin 2)
	AFIO->EXTICR[0] &= ~(0xF<<8); //0000: PA[x] pin

	// Configure EXTI0
	EXTI->RTSR |= (1U<<0); /* Then we would have to decide whether we want to
	interrupt to be triggered by rising edge or falling edge. Over here we will
	use falling edge trigger */

	// Disable the Mask on EXTI0
	EXTI->IMR |= (1U<<0); //Unmask EXTI0//

	 // Set the priority (adjust this value based on your needs)
	 NVIC_SetPriority(EXTI2_IRQn, 6);
	 // Enable EXTI0 IRQ in NVIC
	 NVIC_EnableIRQ(EXTI2_IRQn);

	 // Infinite Loop
	     while (1) {
	      }
	      return 0;
	 }



/*------ FOR RUNNING THE CODE ------*/
// SysTick initialization for 1 ms ticks
void systick_init(void) {
    SysTick->LOAD = 9000; // 1 ms per tick
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

// SysTick handler to increment the ms_ticks counter
void SysTick_Handler(void) {
    ms_ticks++;
}

// Callback for EXTI0 interrupt (LED ON)
static void exti0_callback(void) {
    GPIOC->BSRR |= LEDC13; // Turn LED ON
}

// EXTI0 interrupt handler
void EXTI0_IRQHandler(void) {
    if ((EXTI->PR & LINE0) != 0) { // Check if interrupt is from line 0
        uint32_t current_time = ms_ticks;
        // 1: selected trigger request occurred
        if ((current_time - last_interrupt_time) > DEBOUNCE_DELAY_MS) {
            last_interrupt_time = current_time; //Debouncing mechanism
            EXTI->PR |= LINE0; // Clear pending interrupt flag
            exti0_callback();  // Call callback function
        }
    }
}


