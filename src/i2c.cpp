#include "i2c.hpp"

bool transmission_pending = false;
// bool start_symbol_sent = false;
// bool address_sent = false;
// bool data_register_empty = false;

void init_i2c()
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // Program peripheral input clock. PCLK1 is 24 MHz.
    // I2C1->CR2 |= (24 << I2C_CR2_FREQ_Pos);
    I2C1->CR2 |= (0x18 << I2C_CR2_FREQ_Pos);

    /*
     * Configure clock control registers to 100 kHz (Standard speed, Sm) PCLK1
     * runs at 24 MHz and the register value is
     * T/TPCLK1 = 10000 ns / 41.667 ns = 240.
     */
    // I2C1->CCR |= (240 << I2C_CCR_CCR_Pos);
    I2C1->CCR |= (0xF0 << I2C_CCR_CCR_Pos);

    /*
     * Configure the rise time register. Max rise time for Sm mode is 1000 ns.
     * The value in this register should be the max SCL rise time, divided by
     * the PCLK1 period, plus one: 1000 ns / 41.667 ns + 1 = 24 + 1 = 25.
     */
    // I2C1->TRISE |= (25 << I2C_TRISE_TRISE_Pos);
    I2C1->TRISE |= (0x19 << I2C_TRISE_TRISE_Pos);

    // // Enable buffer and event interrupts.
    // I2C1->CR2 |= (I2C_CR2_ITBUFEN & I2C_CR2_ITEVTEN);

    // Enable the I2C peripheral.
    I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_write_byte(char b)
{
    // while (!data_register_empty);
    // data_register_empty = false;
    while (!(I2C1->SR1 & I2C_SR1_TXE));
    I2C1->DR = b;
}

/*
 * Primary transmitter. Sends 7-bit addresses.
 */
void i2c_write_data(const char* data, uint8_t addr)
{
    // Wait for any pending transmissions.
    while (transmission_pending);

    transmission_pending = true;

    // Generate single start symbol.
    I2C1->CR1 |= I2C_CR1_START;
    I2C1->CR1 &= ~I2C_CR1_START;  // TODO needed?

    // Wait for start symbol confirmation.
    // while (!start_symbol_sent);
    // start_symbol_sent = false;
    while (!(I2C1->SR1 & I2C_SR1_SB));
    GPIOC->BSRR ^= GPIO_BSRR_BR13;

    // Send address.
    i2c_write_byte(addr << 1);

    // Wait for address confirmation.
    // while (!address_sent);
    // address_sent = false;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    // Send data.
    for (const char* b = data; *data; data++)
        i2c_write_byte(*b);

    // Send stop symbol.
    I2C1->CR1 |= I2C_CR1_STOP;
}
