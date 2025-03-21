#include "syscall.h"

// A simple test printing out CPU Vendor.
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
            write(STDOUT, vendor_id, k);
            exit(0);
        }
        i++;
    }
    exit(1);
}
