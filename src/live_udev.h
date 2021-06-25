#ifndef __LIVE_UDEV__

#include <libudev.h>
#include <glib.h>
//#include <gmodule.h>
//#include "log.h"

struct live_udev {
	struct udev *udev;
	struct udev_monitor *udev_monitor; 
	struct	GSList	*care_dev_list;
	gint source_id;
};


typedef int (*live_udev_device_add_func)(struct udev_device *device);

struct live_udev_device_info {
	gchar *subsystem;
	gchar *name;
	live_udev_device_add_func func_add_device;
	
};

int live_udev_init(void);


#endif
