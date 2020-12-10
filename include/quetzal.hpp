#ifndef QUETZAL_HPP
#define QUETZAL_HPP

#include <stm32f1xx.h>

#include "oscillator.hpp"
#include "serial.hpp"
#include "test_language_features.hpp"

void blink();
void init_sram_sections();
void main();

#endif /* QUETZAL_HPP */
