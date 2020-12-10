#include "quetzal.hpp"

constexpr uint32_t USART_BAUD = 9600;

void blink()
{
    int ctr;
    ctr = (8000000 / 3) / 2 * 6;
    // each loop iteration takes 3 cycles to execute.
    while (ctr) {
        asm ("");
        --ctr;
    }
    GPIOC->BRR = 1 << 13;
    ctr = (8000000 / 3) / 2 * 6;
    // each loop iteration takes 3 cycles to execute.
    while (ctr) {
        asm ("");
        --ctr;
    }
    GPIOC->BSRR = 1 << 13;
}

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
    GPIOC->BSRR = GPIO_BRR_BR13;

    // Initialize SRAM sections.
    init_sram_sections();

    // Enable GPIO and hang if tests fail.
    if (!test_all_language_features())
    {
        GPIOC->BRR = GPIO_BRR_BR13;
        while (1);
    }

    init_oscillator();
    init_serial(USART_BAUD);

    while (1)
    {
        usartWriteStr("hello!\r\n");
        blink();
    }
}
