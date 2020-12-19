#include "quetzal.hpp"

constexpr uint32_t USART_BAUD = 9600;

/*
 * Allowed to return void type since we're in a freestanding environment.
 */
void main()
{
    // Set up GPIO C13 (green light) for LED control, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF13_1);  // GPIO push-pull
    GPIOC->CRH |= (GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1);  // output @ 50 MHz
    GPIOC->BSRR = GPIO_BSRR_BR13;

    // Set up GPIO A11, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH &= ~(GPIO_CRH_CNF11_0 | GPIO_CRH_CNF11_1);  // GPIO push-pull
    GPIOA->CRH |= (GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1);  // output @ 50 MHz
    GPIOA->BSRR |= GPIO_BSRR_BR11;

    // Set GPIO B12 as external interrupt input with internal pull-up.
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRH &= ~(GPIO_CRH_CNF12_0 | GPIO_CRH_CNF12_1);  // clear CNF bits
    GPIOB->CRH |= GPIO_CRH_CNF12_1;  // input pull-up/-down
    GPIOB->ODR |= GPIO_ODR_ODR12;  // pull-up

    // Configure AFIO to map PB12 to EXTI.
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PB;

    // Set up EXTI 12 for external interrupts via GPIO B12.
    EXTI->IMR |= EXTI_IMR_MR12;  // Unmask interrupts
    EXTI->FTSR |= EXTI_FTSR_TR12;  // Falling trigger

    // Enable EXTI12 interrupt.
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 3);

    init_sysclk();
    // init_tim2();
    // init_tim3();
    init_tim4();
    // init_serial(USART_BAUD);

    GPIOC->BSRR = GPIO_BSRR_BR13;

    while (1)
        __WFI();
}
