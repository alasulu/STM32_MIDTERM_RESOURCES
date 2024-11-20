//#include "stm32f107xx.h"
//
//void initClockHSI(void);
//void initClockHSE(void);
//void initClockPLL(void);
//void delay(uint32_t time);
//
//int main() {
//    // Initialize the clock to use PLL as the system clock
//    initClockPLL();
//
//    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPAEN); // Enable port D clock
//
//    // Configure Port D pins 0 and 1 as outputs
//	 GPIOD->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
//    GPIOD->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5);
//
//	  // Configure Port A pin 3 as input
//	  GPIOA->CRL &= ~(GPIO_CRL_MODE3);
//	  GPIOA->CRL &= ~(GPIO_CRL_CNF3_1);
//
//	  GPIOD->ODR |= (GPIO_ODR_ODR0); // Set Pin 0 HIGH
//
//    while (1) {
//        // Check the state of pin 3 of Port A
//        if ((GPIOA->IDR & GPIO_IDR_IDR3) == GPIO_IDR_IDR3) {
//						if ((GPIOD->ODR & GPIO_ODR_ODR0) == GPIO_ODR_ODR0){
//								GPIOD->ODR ^= GPIO_ODR_ODR0;
//								GPIOD->ODR ^= GPIO_ODR_ODR1;
//								delay(1454545);
//						}
//						else if ((GPIOD->ODR & GPIO_ODR_ODR1) == GPIO_ODR_ODR1){
//								GPIOD->ODR ^= GPIO_ODR_ODR1;
//								GPIOD->ODR ^= GPIO_ODR_ODR5;
//								delay(1454545);
//						}
//						else if ((GPIOD->ODR & GPIO_ODR_ODR5) == GPIO_ODR_ODR5){
//								GPIOD->ODR ^= GPIO_ODR_ODR5;
//								GPIOD->ODR ^= GPIO_ODR_ODR4;
//								delay(1454545);
//						}
//						else if ((GPIOD->ODR & GPIO_ODR_ODR4) == GPIO_ODR_ODR4){
//								GPIOD->ODR ^= GPIO_ODR_ODR4;
//								GPIOD->ODR ^= GPIO_ODR_ODR0;
//								delay(1454545);
//						}
//        }
//    }
//    return 0;
//}
//
//// Function to introduce a delay
//void delay(uint32_t time) {
//    while (time--);
//}
//
///**
// * @brief Initializes the clock to use 8MHz HSI as the system clock.
// */
//void initClockHSI(void) {
//    RCC->CR |= RCC_CR_HSION; // Enable internal HSI (RC)
//    while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY); // Wait for HSI to be ready
//
//		//RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
//    RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
//    RCC->CFGR |= RCC_CFGR_SW_HSI; // Set HSI as the system clock
//
//    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait for HSI to be the system clock
//}
//
//void initClockHSE(void) {
//    RCC->CR |= RCC_CR_HSEON; // Enable external HSE (RC)
//    while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY); // Wait for HSE to be ready
//
//		//RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
//    RCC->CFGR &= ~(RCC_CFGR_SW); // Clear SW bits
//    RCC->CFGR |= RCC_CFGR_SW_HSE; // Set HSE as the system clock
//
//    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE); // Wait for HSE to be the system clock
//}
//
//void initClockPLL(void){
//
//	// Set HSI as the system clock
//	RCC->CFGR &= ~(0x3 << 0);  // Clear bits 1:0, setting SW to 00 (HSI as system clock)
//
//	// Wait for HSI to be the system clock
//	while ((RCC->CFGR & (0x3 << 2)) != 0x0);  // Check the SWS bits in RCC_CFGR
//
//	// Disable the PLL
//	RCC->CR &= ~(0x1<<24); // 0: PLL OF
//	while ((RCC->CR & (0x1 << 25)) != 0x0);
//
//	// Set HSI/2 as PLL entry clock source
//	RCC->CFGR &= ~(0x1<<16); //  0: HSI oscillator clock / 2 selected as PLL input clock
//
//	// Set PLL multiplication factor
//	RCC->CFGR &= ~(0xF<<18); // Clear PLL Multiplication factor bits
//	RCC->CFGR |= (0xC<<18); //  PLL input clock x 14
//
//	// Enable PLL (RC)
//	RCC->CR |= (0x1<<24); // 1: PLL ON
//
//	// Wait for PLL to be ready
//	while ((RCC->CR && (0x1<<25)) != 1); /*  PLL clock ready flag
//	Set by hardware to indicate that the PLL is locked. */
//
//	// Clear SW bits
//	RCC->CFGR &= ~(0x3<<0);
//
//	// Set PLL as the system clock
//	RCC->CFGR |= (0x2<<0); //  10: PLL selected as system clock
//
//	// Wait for PLL to be the system clock
//	while((RCC->CFGR & (0x3<<2)) != (0x2<<2));
//}
