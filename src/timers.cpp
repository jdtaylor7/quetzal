#include "timers.hpp"

/*
 * Operates at 1 kHz. Source is APB1, which runs at 24 MHz. Therefore, must
 * divide by 24k. Auto-reload (ARR) value of 24k fits in the 16-bit ARR
 * register, so prescaling is not required.
 */
void init_tim2()
{
    // Configure APB1.
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;

    // Configure TIM2.
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->ARR = 24'000 - 1;

    // Start TIM2.
    TIM2->CR1 |= TIM_CR1_CEN;

    // Clear and enable interrupts.
    TIM2->SR = 0;

    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 15);
}

/*
 * Operates at 1 Hz. Source is APB1, which runs at 24 MHz. Therefore, must
 * divide by 24M. Auto-reload (ARR) value is 24k, prescaler (PSC) is 1k.
 */
void init_tim3()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM3RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM3RST;

    // Configure TIM3.
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->ARR = 24'000 - 1;
    TIM3->PSC = 1'000;

    // Start TIM3.
    TIM3->CR1 |= TIM_CR1_CEN;

    // Clear and enable interrupts.
    TIM3->SR = 0;

    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_SetPriority(TIM3_IRQn, 15);
}
