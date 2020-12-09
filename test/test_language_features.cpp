#include "test_language_features.hpp"

char test_uninit_global;
char test_init_global = 'b';

bool test_uninit_globals()
{
    if (test_uninit_global != 0) return false;
    test_uninit_global = 'a';
    if (test_uninit_global != 'a') return false;
    return true;
}

bool test_init_globals()
{
    if (test_init_global != 'b') return false;
    test_init_global = 'c';
    if (test_init_global != 'c') return false;
    return true;
}

bool test_all_language_features()
{
    if (!test_uninit_globals()) return false;
    if (!test_init_globals()) return false;

    return true;
}
