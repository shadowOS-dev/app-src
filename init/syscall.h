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

#define BIT(x) (1U << (x))

// open() flags
#define O_CREATE BIT(0)

// STDOUT file descriptor
#define STDOUT 0

typedef struct stat
{
    uint64_t size;
    uint32_t flags;
    uint32_t type;
    uint32_t uid;
    uint32_t gid;
    uint32_t mode;
} stat_t;

long syscall(uint64_t number, uint64_t arg1, uint64_t arg2, uint64_t arg3);

void write(int fd, const char *buf, uint64_t size);
void exit(int status);
int open(const char *pathname, uint64_t flags, uint8_t kind);
int close(int fd);
int read(int fd, char *buf, uint64_t size);
int stat(int fd, stat_t *stat);
int setuid(uint32_t uid);
int setgid(uint32_t gid);
int ioctl(int fd, uint32_t cmd, uint32_t arg);
int getpid(void);

#endif // SYSCALL_H
