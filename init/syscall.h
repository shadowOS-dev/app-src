#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

// Define syscall IDs
#define SYS_exit 0
#define SYS_open 1
#define SYS_close 2
#define SYS_write 3
#define SYS_read 4
#define SYS_stat 5
#define SYS_setuid 6
#define SYS_setgid 7
#define SYS_ioctl 8
#define SYS_getpid 9
#define SYS_uname 10

#define BIT(x) (1U << (x))
#define O_CREATE BIT(0)
#define stdout 1

typedef struct stat
{
    uint64_t size;
    uint32_t flags;
    uint32_t type;
    uint32_t uid;
    uint32_t gid;
    uint32_t mode;
} stat_t;

typedef struct
{
    char sysname[64];
    char nodename[64];
    char release[64];
    char version[128];
    char machine[64];
    char build[32];
    char os_type[64];
} uname_t;

static inline long syscall(uint64_t number, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5)
{
    long ret;
    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(number), "b"(arg1), "c"(arg2), "d"(arg3), "S"(arg4), "D"(arg5)
        : "memory");
    return ret;
}

static inline void exit(int status)
{
    syscall(SYS_exit, status, 0, 0, 0, 0);
}

static inline int write(int fd, const char *buf, uint64_t size)
{
    return (int)syscall(SYS_write, fd, (uint64_t)buf, size, 0, 0);
}

static inline int open(const char *pathname, uint64_t flags, uint8_t kind)
{
    return (int)syscall(SYS_open, (uint64_t)pathname, flags, kind, 0, 0);
}

static inline int close(int fd)
{
    return (int)syscall(SYS_close, fd, 0, 0, 0, 0);
}

static inline int read(int fd, char *buf, uint64_t size)
{
    return (int)syscall(SYS_read, fd, (uint64_t)buf, size, 0, 0);
}

static inline int stat(int fd, stat_t *stat)
{
    return (int)syscall(SYS_stat, fd, (uint64_t)stat, 0, 0, 0);
}

static inline int setuid(uint32_t uid)
{
    return (int)syscall(SYS_setuid, uid, 0, 0, 0, 0);
}

static inline int setgid(uint32_t gid)
{
    return (int)syscall(SYS_setgid, gid, 0, 0, 0, 0);
}

static inline int ioctl(int fd, uint32_t cmd, uint32_t arg)
{
    return (int)syscall(SYS_ioctl, fd, cmd, arg, 0, 0);
}

static inline int getpid(void)
{
    return (int)syscall(SYS_getpid, 0, 0, 0, 0, 0);
}

static inline int uname(uname_t *buf)
{
    return (int)syscall(SYS_uname, (uint64_t)buf, 0, 0, 0, 0);
}

#endif // SYSCALL_H
