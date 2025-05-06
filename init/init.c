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

void put(const char *data, size_t length)
{
    if (data == NULL || length == 0)
        return;

    ssize_t result = write(stdout, data, length);
    if (result < 0)
    {
    }
}

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
        put(buffer, length);
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
    printf("Hello, World (using %s)!\n", "printf");
    exit(0);
}
