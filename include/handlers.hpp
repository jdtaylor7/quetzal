#ifndef INTERRUPTS_HPP
#define INTERRUPTS_HPP

#include <stm32f1xx.h>

#include "quetzal.hpp"

void reset_handler();
void default_handler();
void tim2_handler();
void tim3_handler();

#endif /* INTERRUPTS_HPP */
