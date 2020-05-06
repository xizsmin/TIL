


#define trace(fmt, ...) { printk(KERN_INFO "[%s:%d] %s "fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }


// to show filename only, without full-path:
#include <linux/string.h>

#define __FILENAME__ strrchr("/" __FILE__, '/') + 1
#define trace(fmt, ...) { printk(KERN_INFO "[%s:%d] %s "fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }

