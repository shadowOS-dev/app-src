#include "syscall.h"

void _start(void)
{
    // Print some fancy bytes to clear screen
    write(STDOUT, "\033[2J\033[H\033[?25l ", 13);

    // Print message
    write(STDOUT, "this init script currently does nothing but eh, atleast it runs :^)\n", 71);
    exit(0);
}
