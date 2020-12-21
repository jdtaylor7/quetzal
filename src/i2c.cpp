#include "i2c.hpp"

void init_i2c()
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // Program peripheral input clock.
    I2C1->CR2 |= (24 << I2C_CR2_FREQ_Pos);

    /*
     * Configure clock control registers to 100 kHz (Standard speed, Sm) PCLK1
     * runs at 24 MHz and the register value is
     * T/TPCLK1 = 10000 ns / 41.667 ns = 240.
     */
    I2C1->CCR |= (240 << I2C_CCR_CCR_Pos);

    /*
     * Configure the rise time register. Max rise time for Sm mode is 1000 ns.
     * The value in this register should be the max SCL rise time, divided by
     * the PCLK1 period, plus one: 1000 ns / 41.667 ns + 1 = 24 + 1 = 25.
     */
    I2C1->TRISE |= (25 << I2C_TRISE_TRISE_Pos);

    // Enable the I2C peripheral.
    I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_write_byte(uint8_t b)
{

}

/*
 * Primary transmitter.
 */
void i2c_write_str(const char* str, uint16_t addr)
{
    // Generate start symbol.

    // Send data.

}
