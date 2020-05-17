// http://jake.dothome.co.kr/proc/

#ifndef __FOO_H__
#define __FOO_H__

#include <linux/mutex.h>
#include <linux/list.h>

struct foo_info {
	int a;
	int b;
	struct list_head list;
};

extern struct mutex foo_lock;
extern struct list_head foo_list;

#endif

