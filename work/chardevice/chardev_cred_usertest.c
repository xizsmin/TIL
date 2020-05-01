#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "chardev.h"

int main(int argc, char **argv)
{
	int fd, ret;

	if ( (fd = open("/dev/chardev0", O_NOCTTY)) < 0) {
		printf("Failed to open chardev0: abort\n");
		goto _OUT;
	}
	ret = ioctl(fd, BE_ROOT);
	if (ret < 0) {
		printf("ioctl failed with err=%d: abort\n", ret);
		goto _OUT;
	}
	close(fd);

	// shell opens with root priv., test with:
	// # id
	execl("/bin/sh", "sh", NULL);

_OUT:
	return 0;
}
