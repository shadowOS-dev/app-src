#include "syscall.h"

void _start(void)
{
    setuid(1); // hehe, will cause write to error
    write(stdout, "Hello, World!\n", 14);
    exit(0);
}
