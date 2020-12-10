#include "serial.hpp"

constexpr uint32_t HSI = 8000000;  // High-speed internal clock

void init_serial(uint32_t baud)
{
    uint16_t usart_divider = static_cast<uint16_t>(HSI / (16 * baud));

    // Set up USART1 peripheral.
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // Enable USART1 peripheral
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE;
    USART1->CR2 = 0;
    USART1->CR3 = 0;
    USART1->BRR = usart_divider << 4;

    // Set up GPIOA 9 for USART1 TX alternative function.
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~(GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_0);
}

void usartWriteChar(unsigned char c)
{
    while (!(USART1->SR & USART_SR_TXE)) {}
    USART1->DR = c;
}

// void usartWriteStr(const std::string& str)
// {
//     for (unsigned char c : str)
//         usartWriteChar(c);
// }

void usartWriteStr(const char* str)
{
    for (const char* c = str; *c; c++)
        usartWriteChar(*c);
}
