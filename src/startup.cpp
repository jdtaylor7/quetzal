#include "startup.hpp"

void init_sram_sections()
{
    extern uint32_t __bss_start;
    extern uint32_t __bss_end;

    extern uint32_t __data_start_flash;
    extern uint32_t __data_start_ram;
    extern uint32_t __data_size;

    // Clear bss.
    for (uint32_t* dst = &__bss_start; dst < &__bss_end; dst++)
        *dst = 0;

    // Copy data into ram.
    uint32_t* src = &__data_start_flash;
    uint32_t* dst = &__data_start_ram;
    uint32_t* dend = dst + ((uint32_t)&__data_size);

    while (dst < dend)
        *dst++ = *src++;
}

void startup()
{
    init_sram_sections();
}
