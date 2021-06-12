#include <libudev.h>
#include "log.h"

#ifdef FBDEV
static int enumerate_fbdev(void)
{
	dbg_fbdev("Enumerate fbdev begin ....\n");
}

int fbdev_init()
{
	enumerate_fbdev();
}

#endif