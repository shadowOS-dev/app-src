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

// Printf stuff, for debugging
void put(const char *data, size_t length)
{
    write(stdout, data, length);
}

int vprintf(const char *fmt, va_list args)
{
    char buffer[1024];
    int length = npf_vsnprintf(buffer, sizeof(buffer), fmt, args);

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

// Entry
void _start(void)
{
    printf("Hello, World (using printf)!\n");
    exit(0);
}
