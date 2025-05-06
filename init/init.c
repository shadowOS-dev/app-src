#include "syscall.h"

void _start(void)
{
    write(0, "Try writing something: ", 24);
    int fd = open("/dev/ps2kb", 0, 0);
    if (fd == -1)
    {
        write(0, "Failed to open keyboard\n", 25);
        exit(1);
    }

    write(0, "keyboard is open!\n", 19);
    exit(0);
}
