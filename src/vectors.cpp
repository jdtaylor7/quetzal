#include "interrupts.hpp"

extern char __stack_end;

extern void (* const vectors[])() __attribute__ ((section(".vectors"))) = {
                (void (*)())&__stack_end,
                reset_handler,
};
