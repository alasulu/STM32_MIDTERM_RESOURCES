#include "stm32f10x.h"

void initClockHSI(void);
void EXTI0_IRQHandler(void);
void delay(uint32_t time);

int main() {
    
		// Initialize the clock to use PLL as the system clock
    initClockHSI();
		
		RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPAEN);
	
		GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
		GPIOA->CRL |= GPIO_CRL_CNF0_1; // Input pull-up
		
		GPIOD->CRL |= (GPIO_CRL_MODE0);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0);
	
	  GPIOD->ODR ^= (1 << 0) ;
	
		// Enable the AFIO clock
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
		// Connect EXTI0 to GPIOA pin 0
		AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0);
		AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;
		
		// Configure EXTI0
		EXTI->RTSR |= EXTI_RTSR_TR0;//Enable rising edge trigger
		EXTI->FTSR &= EXTI_RTSR_TR0;//Disable falling edge trig.
		
		// Disable the Mask on EXTI0
		EXTI->IMR |= EXTI_IMR_MR0;

		// Set the priority (adjust this value based on your needs)
		NVIC_SetPriority(EXTI0_IRQn, 2);
		
		// Enable EXTI0 IRQ in NVIC
		NVIC_EnableIRQ(EXTI0_IRQn);
		
		// Infinite Loop
    while (1) {
			
    }
		
    return 0;
}

void EXTI0_IRQHandler(void) {
    // Interrupt handling code here
		GPIOD->ODR ^= (1 << 0) ;
    // Clear the EXTI line pending bit
    EXTI->PR |= EXTI_PR_PR0;
	  delay(800);
}

// Function to introduce a delay
void delay(uint32_t time) {
    while (time--);
}


void initClockHSI(void) {
    RCC->CR |= RCC_CR_HSION; // Enable internal HSI (RC)

    while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY); // Wait for HSI to be ready

    RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSI; // Set HSI as the system clock

    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for HSI to be the system clock
}
