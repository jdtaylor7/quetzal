#ifndef SERIAL_HPP
#define SERIAL_HPP

// #include <string>

#include <cstdint>

#include <stm32f1xx.h>

void init_serial(uint32_t baud);

void usartWriteChar(unsigned char c);

// void usartWriteStr(const std::string& str);

void usartWriteStr(const char* str);

#endif /* SERIAL_HPP */
