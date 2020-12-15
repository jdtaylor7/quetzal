#include "quetzal.hpp"

constexpr uint32_t USART_BAUD = 9600;

// Allowed to return void type since we're in a freestanding environment.
void main()
{
    // Set up GPIOC 13 (green light) for LED control, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF13_1);
    GPIOC->CRH |= (GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1);
    GPIOC->BSRR = GPIO_BSRR_BR13;

    // Set up GPIOB 12, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRH &= ~(GPIO_CRH_CNF12_0 | GPIO_CRH_CNF12_1);
    GPIOB->CRH |= (GPIO_CRH_MODE12_0 | GPIO_CRH_MODE12_1);
    GPIOB->BSRR = GPIO_BSRR_BR12;

    init_sysclk();
    init_tim2();
    init_tim3();
    // init_serial(USART_BAUD);

    while (1)
    {
        __WFI();
    }
}
