#include "syscall.h"

void _start(void)
{
    // Print out /root/welcome.txt
    int fd = open("/root/welcome.txt");
    if (fd == -1)
    {
        exit(1);
    }

    stat_t info;
    stat(fd, &info);
    char buf[info.size];
    if (read(fd, buf, info.size) < 0)
    {
        exit(1);
    }

    write(STDOUT, buf, info.size);
    close(fd);
    exit(0);
}
