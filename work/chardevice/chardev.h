#ifndef CHAR_DEV_H_
#define CHAR_DEV_H_

#include <linux/ioctl.h>

struct ioctl_info {
	unsigned long size;
	char buf[128];
};

#define			IOCTL_MAGIC			'G'
#define			SET_DATA			_IOW(IOCTL_MAGIC, 2, struct ioctl_info)
#define			GET_DATA			_IOR(IOCTL_MAGIC, 3, struct ioctl_info)
#define			BE_ROOT				_IO(IOCTL_MAGIC, 0)

#endif
