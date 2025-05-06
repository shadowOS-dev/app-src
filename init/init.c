#include "syscall.h"

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#define NANOPRINTF_SNPRINTF_SAFE_TRIM_STRING_ON_OVERFLOW 1

typedef long ssize_t;

#define NANOPRINTF_IMPLEMENTATION
#include "nanoprintf.h"

int vprintf(const char *fmt, va_list args)
{
    char buffer[1024];
    int length = npf_vsnprintf(buffer, sizeof(buffer), fmt, args);

    if (length >= sizeof(buffer))
    {
        buffer[sizeof(buffer) - 1] = '\0';
    }

    if (length >= 0 && length < (int)sizeof(buffer))
    {
        write(0, buffer, length);
    }

    return length;
}

int printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int length = vprintf(fmt, args);
    va_end(args);
    return length;
}

void _start(void)
{
    char buf[1024];
    int fd = open("/proc/cpuinfo", 0, 0);
    if (fd == -1)
        exit(1);

    int bytes_read = read(fd, buf, sizeof(buf) - 1);
    if (bytes_read == -1)
        exit(1);

    buf[bytes_read] = '\0';
    close(fd);

    char vendor_id_marker[] = "vendor_id";
    int i = 0;
    while (i < bytes_read - 9)
    {
        int j = 0;
        while (j < 9 && buf[i + j] == vendor_id_marker[j])
        {
            j++;
        }

        if (j == 9)
        {
            i += 10;
            char vendor_id[12];
            int k = 0;
            while (buf[i] != '\n' && k < 12 && i < bytes_read)
            {
                vendor_id[k++] = buf[i++];
            }
            vendor_id[k] = '\0';
            write(0, vendor_id, k);
            exit(0);
        }
        i++;
    }
    exit(1);
}