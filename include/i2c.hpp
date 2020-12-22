#ifndef I2C_HPP
#define I2C_HPP

#include <stm32f1xx.h>

void init_i2c();
void i2c_write_byte(char b);
void i2c_write_data(const char* data, uint8_t addr);

#endif /* I2C_HPP */
