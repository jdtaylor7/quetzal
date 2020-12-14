#include "clocks.hpp"

void init_sysclk()
{
    // Enable HSE.
    RCC->CR |= RCC_CR_HSEON;

    // Wait for HSE to be stable.
    while (!(RCC->CR & RCC_CR_HSERDY));

    // Configure PLL. 8 MHz external oscillator * 6 = 48 MHz. APB1 must be
    // <36 MHz.
    RCC->CFGR |= (RCC_CFGR_PLLMULL6 | RCC_CFGR_PLLSRC | RCC_CFGR_PPRE1_DIV2);

    // Enable PLL.
    RCC->CR |= RCC_CR_PLLON;

    // Wait for PLL to be stable.
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // Ensure USART1 not currently transmitting so as to not interrupt.
    if (RCC->APB2ENR & RCC_APB2ENR_USART1EN)
    {
        while ((USART1->SR & (USART_SR_TXE | USART_SR_TC)) !=
            (USART_SR_TXE | USART_SR_TC));
    }

    // Switch SYSCLK to PLL.
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait for confirmation of clock switch.
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));
}
