#include "syscall.h"

void display_vendor()
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

    char vendor_id_marker[] = "vendor_id:";
    int i = 0;
    while (i < bytes_read - 10)
    {
        int j = 0;
        while (j < 10 && buf[i + j] == vendor_id_marker[j])
        {
            j++;
        }

        if (j == 10)
        {
            i += 11;

            char vendor_id[13];
            int k = 0;
            while (buf[i] != '\n' && k < 12 && i < bytes_read)
            {
                vendor_id[k++] = buf[i++];
            }
            vendor_id[k] = '\0';

            write(STDOUT, vendor_id, k);
        }
        i++;
    }
}

void _start(void)
{
    // Display vendor
    write(STDOUT, "CPU: ", 5);
    display_vendor();
    write(STDOUT, "\n", 1);

    // Test some ioctl stuff (unsupported on stdout, for now)
    ioctl(STDOUT, 0, 0);

    exit(0);
}
