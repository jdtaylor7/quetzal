#include <stm32f1xx.h>

#include "serial.hpp"

extern char __stack_end;

constexpr uint32_t USART_BAUD = 9600;

void blink()
{
    int ctr;
    ctr = (8000000 / 3) / 2 / 1;
    // each loop iteration takes 3 cycles to execute.
    while (ctr) {
        asm ("");
        --ctr;
    }
    GPIOC->BRR = 1 << 13;
    ctr = (8000000 / 3) / 2 / 1;
    // each loop iteration takes 3 cycles to execute.
    while (ctr) {
        asm ("");
        --ctr;
    }
    GPIOC->BSRR = 1 << 13;
}

void mainFn() {
    // Set up GPIOC 13 (green light) for LED control, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH = 0b0100'0100'0011'0100'0100'0100'0100'0100;
    GPIOC->BSRR = GPIO_BRR_BR13;

    init_serial(USART_BAUD);

    while (1)
    {
        usartWriteStr("hello!\r\n");
        blink();
    }
}

extern void (* const vectors[])() __attribute__ ((section(".vectors"))) = {
                (void (*)())&__stack_end,
                mainFn,
};
