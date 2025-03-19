#include "syscall.h"

long syscall(uint64_t number, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    long ret;
    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3)
        : "memory");
    return ret;
}

void write(int fd, const char *buf, uint64_t size)
{
    syscall(SYS_write, fd, (uint64_t)buf, size);
}

void exit(int status)
{
    syscall(SYS_exit, status, 0, 0);
}

int open(const char *pathname, uint64_t flags, uint8_t kind)
{
    return (int)syscall(SYS_open, (uint64_t)pathname, flags, kind);
}

int close(int fd)
{
    return (int)syscall(SYS_close, fd, 0, 0);
}

int read(int fd, char *buf, uint64_t size)
{
    return (int)syscall(SYS_read, fd, (uint64_t)buf, size);
}

int stat(int fd, stat_t *stat)
{
    return (int)syscall(SYS_stat, fd, (uint64_t)stat, 0);
}
