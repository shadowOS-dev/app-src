#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

#define STDOUT 0
#define SYS_exit 0
#define SYS_open 1
#define SYS_close 2
#define SYS_write 3
#define SYS_read 4
#define SYS_stat 5

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
int open(const char *pathname);
int close(int fd);
int read(int fd, char *buf, uint64_t size);
int stat(int fd, stat_t *stat);

#endif // SYSCALL_H
