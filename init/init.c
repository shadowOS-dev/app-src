#include "syscall.h"

void _start(void)
{
    // todo
    write(STDOUT, "this init script currently does nothing but eh, atleast it runs :^)\n", 71);
    exit(0);
}
