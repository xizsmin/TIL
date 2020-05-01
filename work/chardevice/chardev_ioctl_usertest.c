#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include "chardev.h"

int main(int argc, char **argv)
{
	int fd;
	struct ioctl_info set_info;
	struct ioctl_info get_info;

	set_info.size = 100;
	strncpy(set_info.buf, "AAAAAAAA", 8);

	if ((fd = open("/dev/chardev0", O_RDWR)) < 0) \
		printf("Failed to open /dev/chardev0\n");

	if (ioctl(fd, SET_DATA, &set_info) < 0) \
		printf("Failed to set data\n");

	if (ioctl(fd, GET_DATA, &get_info) < 0) \
		printf("Failed to get data\n");

	printf("get_info.size: %ld, get_info.buf: %s\n", get_info.size, get_info.buf);
	if (close(fd)) \
		printf("Failed to close\n");
	return 0;
}
