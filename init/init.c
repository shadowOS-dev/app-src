#include "syscall.h"

void _start(void)
{
    // Create /test.txt
    int fd = open("/test.txt", 0, 0); // 0x0002 -> regular file.
    if (fd == -1)
    {
        exit(1);
    }

    // Write some stuff into it
    write(fd, "Hello\n", 7);

    // Print the contents on out to stdout
    stat_t s;
    stat(fd, &s);
    char buf[s.size];
    read(fd, buf, s.size);
    write(STDOUT, buf, s.size);
    exit(0);
}
