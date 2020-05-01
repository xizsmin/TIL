#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define TEXT_LEN		12

int main(void)
{
	static char buff[256];
	int fd;

	// open chardev0, created and registered by chardev module
	if ((fd = open("/dev/chardev0", O_RDWR)) < 0) {
		printf("Failed to open /dev/chardev0: abort\n");
	}
	// read from chardev0: data originally stored in kernel buffer
	if (read(fd, buff, TEXT_LEN) < 0) {
		printf("Failed to read\n");
	} else printf("%s\n", buff);
	
	// write new data to kernel
	if (write(fd, "AAAAAAAAAAA", TEXT_LEN) < 0) {
		printf("Failed to write string\n");
	}

	if (read(fd, buff, TEXT_LEN) < 0) {
		printf("Failed to read\n");
	} else printf("%s\n", buff);

	if (close(fd)) printf("Failed to close\n");

	return 0;
}
