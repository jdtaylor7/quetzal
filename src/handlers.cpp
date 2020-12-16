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

    // Enable GPIO and hang if tests fail.
    if (!test_all_language_features())
    {
        GPIOC->BRR = GPIO_BRR_BR13;
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
    // GPIOC->ODR ^= GPIO_ODR_ODR13;
}

void exti15_10_handler()
{
    // EXTI12.
    if (EXTI->PR & EXTI_PR_PR12)
    {
        EXTI->PR |= EXTI_PR_PR12;
        GPIOC->ODR ^= GPIO_ODR_ODR13;
    }
}
