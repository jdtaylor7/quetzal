#ifndef SERIAL_HPP
#define SERIAL_HPP

// #include <string>

#include <cstdint>

#include <stm32f1xx.h>

void init_serial(uint32_t baud);

void usart_write_char(unsigned char c);

// void usart_write_str(const std::string& str);

void usart_write_str(const char* str);

#endif /* SERIAL_HPP */
