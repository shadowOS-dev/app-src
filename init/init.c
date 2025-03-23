#include "syscall.h"

void _start(void)
{
    write(stdout, "Hello, World!\n", 14);
    exit(0);
}
