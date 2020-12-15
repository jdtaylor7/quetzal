#include "quetzal.hpp"

constexpr uint32_t USART_BAUD = 9600;

void init_sram_sections()
{
    extern uint32_t __bss_start;
    extern uint32_t __bss_end;

    extern uint32_t __data_start_flash;
    extern uint32_t __data_start_ram;
    extern uint32_t __data_size;

    // Clear bss.
    for (uint32_t* dst = &__bss_start; dst < &__bss_end; dst++)
        *dst = 0;

    // Copy data into ram.
    uint32_t* src = &__data_start_flash;
    uint32_t* dst = &__data_start_ram;
    uint32_t* dend = dst + ((uint32_t)&__data_size);

    while (dst < dend)
        *dst++ = *src++;
}

// Allowed to return void type since we're in a freestanding environment.
void main()
{
    // Set up GPIOC 13 (green light) for LED control, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH = 0b0100'0100'0011'0100'0100'0100'0100'0100;
    // GPIOC->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF13_1);
    // GPIOC->CRH |= (GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1);
    GPIOC->BSRR = GPIO_BSRR_BR13;

    // Set up GPIOB 12, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRH = 0b0100'0100'0100'0011'0100'0100'0100'0100;
    // GPIOB->CRH &= ~(GPIO_CRH_CNF12_0 | GPIO_CRH_CNF12_1);
    // GPIOB->CRH |= (GPIO_CRH_MODE12_0 | GPIO_CRH_MODE12_1);
    GPIOB->BSRR = GPIO_BSRR_BR12;

    // Initialize SRAM sections.
    init_sram_sections();

    // Enable GPIO and hang if tests fail.
    if (!test_all_language_features())
    {
        GPIOC->BRR = GPIO_BRR_BR13;
        while (1);
    }

    init_sysclk();
    init_tim2();
    init_tim3();
    // init_serial(USART_BAUD);

    while (1)
    {
        __WFI();
    }
}
