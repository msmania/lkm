#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "tiny.h"

int main() {
    int ret;
    int fd;
    char msg[] = "Hello, Kernel!";

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        printf("open(%s) failed - %d\n", DEVICE_PATH, errno);
        exit(-1);
    }

    ret = ioctl(fd, IOCTL_CMD, msg);
    printf("ioctl returned %d\n", ret);
    close(fd);
    return ret;
}
