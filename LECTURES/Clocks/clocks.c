#include "stm32f10x.h"

void initClockHSI(void);
void initClockHSE(void);
void initClockPLL(void);
void delay(uint32_t time);

int main() {
    // Initialize the clock to use PLL as the system clock
    initClockPLL();

    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPAEN); // Enable port D clock
	
    // Configure Port D pins 0 and 1 as outputs
	  GPIOD->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5);

	  // Configure Port A pin 3 as input
	  GPIOA->CRL &= ~(GPIO_CRL_MODE3);
	  GPIOA->CRL &= ~(GPIO_CRL_CNF3_1);
		
	  GPIOD->ODR |= (GPIO_ODR_ODR0); // Set Pin 0 HIGH
		
    while (1) {
        // Check the state of pin 3 of Port A
        if ((GPIOA->IDR & GPIO_IDR_IDR3) == GPIO_IDR_IDR3) {
						if ((GPIOD->ODR & GPIO_ODR_ODR0) == GPIO_ODR_ODR0){
								GPIOD->ODR ^= GPIO_ODR_ODR0;
								GPIOD->ODR ^= GPIO_ODR_ODR1;
								delay(1454545);
						}
						else if ((GPIOD->ODR & GPIO_ODR_ODR1) == GPIO_ODR_ODR1){
								GPIOD->ODR ^= GPIO_ODR_ODR1;
								GPIOD->ODR ^= GPIO_ODR_ODR5;
								delay(1454545);
						}
						else if ((GPIOD->ODR & GPIO_ODR_ODR5) == GPIO_ODR_ODR5){
								GPIOD->ODR ^= GPIO_ODR_ODR5;
								GPIOD->ODR ^= GPIO_ODR_ODR4;
								delay(1454545);
						}
						else if ((GPIOD->ODR & GPIO_ODR_ODR4) == GPIO_ODR_ODR4){
								GPIOD->ODR ^= GPIO_ODR_ODR4;
								GPIOD->ODR ^= GPIO_ODR_ODR0;
								delay(1454545);
						}
        }
    }
    return 0;
}

// Function to introduce a delay
void delay(uint32_t time) {
    while (time--);
}

/**
 * @brief Initializes the clock to use 8MHz HSI as the system clock.
 */
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

void initClockPLL(void) {
		// Set HSI as the system clock
		RCC->CFGR &= (~RCC_CFGR_SW);
		RCC->CFGR |= RCC_CFGR_SW_HSI;
		// Wait for HSI to be the system clock
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

		// Disable the PLL
    RCC->CR &= ~RCC_CR_PLLON;
		while ((RCC->CR & RCC_CR_PLLRDY) != 0);
	
		RCC->CFGR &= ~(RCC_CFGR_PLLSRC_HSI_Div2);						// Set HSI/2 as PLL entry clock source
		RCC->CFGR |= (RCC->CFGR & ~RCC_CFGR_PLLMULL) | (RCC_CFGR_PLLMULL_2 | RCC_CFGR_PLLMULL_1 | RCC_CFGR_PLLMULL_3); // Set PLL multiplication to 14
	
		RCC->CR |= RCC_CR_PLLON; // Enable PLL (RC)
    while ((RCC->CR & RCC_CR_PLLRDY) == 1); // Wait for PLL to be ready 
	
		RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Set PLL as the system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait for PLL to be the system clock
}
