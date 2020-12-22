#ifndef INTERRUPTS_HPP
#define INTERRUPTS_HPP

#include <stm32f1xx.h>

#include "quetzal.hpp"
#include "startup.hpp"
#include "test_language_features.hpp"

void reset_handler();
void default_handler();
void tim2_handler();
void tim3_handler();
void tim4_handler();
void exti15_10_handler();
void i2c1_ev_handler();
void i2c1_er_handler();

#endif /* INTERRUPTS_HPP */
