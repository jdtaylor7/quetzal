#include "interrupts.hpp"

void reset_handler()
{
    main();
}

void default_handler()
{
    while (1);
}
