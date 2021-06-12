#include <libudev.h>
#include <glib.h>
//#include <gmodule.h>

#include "live_udev.h"
#include "log"

static struct live_udev live_udev;

int live_udev_add_fbdev(struct udev_device *device);

struct live_udev_device_info *sub_devices = {
	{"graphics", "fb", live_udev_add_fbdev},
	NULL
};

int live_udev_add_fbdev(struct udev_device *device)
{
	dbg_udev("fbdev path: %s", udev_device_get_syspath(device));

	return 0;
}

gboolean live_udev_monitor_device(GIOChannel *channel,
										GIOCondition  condition, 
										gpointer *userdata)
{
	struct udev_monitor *monitor = userdata;
	struct udev_device *device;
	const gchar *name;
	
	device = udev_monitor_receive_device(monitor);
	if (!device)
		return -1;
	name = udev_device_get_sysname(device);
	for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) {
		if (fnmatch(sub_devices[i].subsystem, name, 0))
			continue;
		sub_devices[i].func_add_device(device);
	}
	
	return 0;
}

int live_udev_enumerate_device(struct udev *udev)
{
	struct udev_enumerate * e;
	struct udev_list_entry *entry;
	struct udev_device *device;
	const gchar *path, *name;
	int i;
	
	e = udev_enumerate_new(udev)
	if (!e) {
		g_printerr("udev: failed to create the udev enumerate");
		return -1;
	}

	for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) 
		udev_enumerate_add_match_subsystem(e, sub_devices[i].subsystem);
		
	udev_enumerate_scan_devices(e);
	
	udev_list_entry_foreach(entry, udev_enumerate_get_list_entry(e)) {
		path = udev_list_entry_get_name(entry);

		device = udev_device_new_from_syspath(udev, path);
		if (!device)
			continue;
		name = udev_device_get_sysname(device);
		for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) {
			if (fnmatch(sub_devices[i].subsystem, name, 0))
				continue;
			sub_devices[i].func_add_device(device);
		}
	}

	return 0;
}

int live_udev_init(void)
{
	int fd;
	struct udev *udev;
	GIOChannel *udev_channel;
		
	live_udev = g_new0(struct pio_udev, 1);g_file_get_contents 
	udev = udev_new();
	if (udev == NULL) {
		g_printerr("udev: failed to create the udev");
		return -1;
	}
	live_udev->udev_monitor = udev_monitor_new_from_netlink(udev, "udev");
	if (!live_udev->udev_monitor) {
		g_printerr("udev: failed to create the udev monitor");
		udev_unref(udev);
		return -1;
	}
	
	for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) 
		udev_monitor_filter_add_match_subsystem_devtype(live_udev->udev_monitor, sub_devices[i].subsystem, NULL);

	if (udev_monitor_enable_receiving(live_udev->udev_monitor)) {
		g_printerr("udev: failed to bind the udev monitor");
		udev_monitor_unref(live_udev->udev_monitor);
		return -1;
	}
	
	fd = udev_monitor_get_fd(live_udev->udev_monitor);
	udev_channel = g_io_channel_unix_new(fd);
	g_io_add_watch(udev_channel, G_IO_IN, live_udev_monitor_device, live_udev->udev_monitor);

	live_udev_enumerate_device(udev);

	return 0;
}
