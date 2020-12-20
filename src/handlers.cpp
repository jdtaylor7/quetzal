#include "handlers.hpp"

void reset_handler()
{
    // Set up GPIOC 13 (green light) for LED control, then turn off.
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF13_1);
    GPIOC->CRH |= (GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1);
    GPIOC->BSRR = GPIO_BSRR_BR13;

    // Run all startup code.
    startup();

    // Set GPIO and hang if tests fail.
    if (!test_all_language_features())
    {
        GPIOC->BSRR = GPIO_BSRR_BS13;
        while (1);
    }

    // Put GPIOC 13 back into initial state.
    RCC->APB2ENR = 0;
    GPIOC->CRH &= ~GPIO_CRH_CNF13_Msk;
    GPIOC->CRH |= GPIO_CRH_CNF13_0;
    GPIOC->CRH &= ~GPIO_CRH_MODE13_Msk;

    main();
}

void default_handler()
{
    while (1);
}

void tim2_handler()
{
    TIM2->SR = 0;
    GPIOA->ODR ^= GPIO_ODR_ODR11;
}

void tim3_handler()
{
    TIM3->SR = 0;
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}

/*
 * Runs a debounce check for exti15_10_handler.
 */
void tim4_handler()
{
    TIM4->SR = 0;

    /*
     * If true, debounce test passed and input is valid.
     */
    if (!(GPIOB->IDR & GPIO_IDR_IDR12))
        GPIOA->ODR ^= GPIO_ODR_ODR1;
}

/*
 * Initiates a debounce check to ensure valid input.
 */
void exti15_10_handler()
{
    // EXTI12.
    if (EXTI->PR & EXTI_PR_PR12)
    {
        // Clear interrupt.
        EXTI->PR |= EXTI_PR_PR12;

        // Start TIM4.
        TIM4->CR1 |= TIM_CR1_CEN;
    }
}
