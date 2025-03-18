#include "syscall.h"

void _start(void)
{
    // Print message
    write(STDOUT, "\033cthis init script currently does nothing but eh, atleast it runs :^)\n", 71);
    exit(0);
}
