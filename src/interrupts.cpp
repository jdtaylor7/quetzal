#include "interrupts.hpp"

void reset_handler()
{
    main();
}

void default_handler()
{
    while (1);
}

void tim2_handler()
{
    TIM2->SR = 0;
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}
