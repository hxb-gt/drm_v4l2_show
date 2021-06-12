#define G_LOG_DOMAIN "fbdev"
#include <libudev.h>
#include <glib.h>
#include "config.h"
#include "fbdev.h"
//#include "log.h"

#ifdef FBDEV
static int enumerate_fbdev(void)
{
	struct udev *udev;
	g_debug("Enumerate fbdev begin ....");
	g_info("Enumerate fbdev begin ....");
	g_warning("Enumerate fbdev begin ....");
	g_critical("Enumerate fbdev begin ....");
	g_message("Enumerate fbdev begin ....");
	g_error("Enumerate fbdev begin ....");

	udev = udev_new();
#if 0
	dbg_fbdev("Enumerate fbdev begin ....");
	

	dbg_drm("Enumerate fbdev begin ....");
	dbg_fbdev("Enumerate fbdev begin ....");
	dbg_v4l("Enumerate fbdev begin ....");
	dbg_usb("Enumerate fbdev begin ....");
	dbg_udev("Enumerate fbdev begin ....");
	dbg_func_line();	
#endif
}

int fbdev_init()
{
	enumerate_fbdev();
}

#endif