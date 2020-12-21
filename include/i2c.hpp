#ifndef I2C_HPP
#define I2C_HPP

void init_i2c();
void i2c_write_byte(uint8_t b);
void i2c_write_str(const char* str, uint16_t addr);

#endif /* I2C_HPP */
