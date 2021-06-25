#define G_LOG_DOMAIN "udev"

#include <fnmatch.h>
#include <libudev.h>
#include <glib.h>
//#include <gmodule.h>

#include "live_udev.h"
#include "log.h"

static struct live_udev *live_udev = NULL;

int live_udev_add_fbdev(struct udev_device *device);

const struct live_udev_device_info sub_devices[] = {
	{"graphics", "fb*", live_udev_add_fbdev}
	{"drm", "fb*", live_udev_add_fbdev}
};

int live_udev_add_fbdev(struct udev_device *device)
{
	g_debug("fbdev path: %s", udev_device_get_syspath(device));

	return 0;
}

gboolean live_udev_monitor_device(GIOChannel *channel,
										GIOCondition  condition, 
										gpointer userdata)
{
	int i;
	struct udev_monitor *monitor = userdata;
	struct udev_device *device;
	const gchar *name;

	g_debug("udev monitor receive device");
	device = udev_monitor_receive_device(monitor);
	if (!device)
		return -1;
	name = udev_device_get_sysname(device);
	for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) {
		if (fnmatch(sub_devices[i].name, name, 0))
			continue;
		sub_devices[i].func_add_device(device);
	}
	g_debug("udev monitor process complete");
	return 0;
}

int live_udev_enumerate_device(struct udev *udev)
{
	struct udev_enumerate * e;
	struct udev_list_entry *entry;
	struct udev_device *device;
	const gchar *path, *name;
	gint i;
	
	e = udev_enumerate_new(udev);
	if (!e) {
		g_printerr("udev: failed to create the udev enumerate");
		return -1;
	}
	
	for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) {
		g_debug("enumerate device add subsystem %s", sub_devices[i].subsystem);
		if (udev_enumerate_add_match_subsystem(e, sub_devices[i].subsystem) < 0) {
			g_printerr("udev: udev enumerate add match subsystem %s failded\n", 
						sub_devices[i].subsystem);
			goto err_add_match_subsystem;
		}
	}

	g_debug("enumerate device scan");
	udev_enumerate_scan_devices(e);

	g_debug("enumerate device loop");
	udev_list_entry_foreach(entry, udev_enumerate_get_list_entry(e)) {
		path = udev_list_entry_get_name(entry);
		
		g_debug("enumerate device path: %s", path);
		
		device = udev_device_new_from_syspath(udev, path);
		if (!device)
			continue;
		name = udev_device_get_sysname(device);

		if (!udev_device_get_is_initialized(device)) {
			g_printerr("%-7s - skip unconfigured input device '%s'\n",
				  name,
				  udev_device_get_devnode(device));
			udev_device_unref(device);
			continue;
		}
		
		g_debug("enumerate device name: %s", name);
		for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) {
			if (fnmatch(sub_devices[i].name, name, 0))
				continue;
			sub_devices[i].func_add_device(device);
		}
		udev_device_unref(device);
	}
	udev_enumerate_unref(e);

	return 0;
	
err_add_match_subsystem:
	udev_enumerate_unref(e);
	return -1;
}

int live_udev_init(void)
{
	gint i, fd;
	gint ret;
	struct udev *udev;
	GIOChannel *udev_channel;

	g_debug("live udev init......");
	
	live_udev = g_new0(struct live_udev, 1); 
	if (live_udev == NULL) {
		g_printerr("udev: failed to alloc the live_udev");
		return -1;
	}
	g_debug("udev_new()");
	live_udev->udev = udev_new();
	if (live_udev->udev == NULL) {
		g_printerr("udev: failed to create the udev");
		goto err_create_udev;
	}
	g_debug("udev_monitor_new_from_netlink()");
	live_udev->udev_monitor = udev_monitor_new_from_netlink(live_udev->udev, "udev");
	if (!live_udev->udev_monitor) {
		g_printerr("udev: failed to create the udev monitor");
		goto err_create_udev_monitor;
	}
	
	for (i = 0; i < G_N_ELEMENTS(sub_devices); i++) 
		udev_monitor_filter_add_match_subsystem_devtype(live_udev->udev_monitor, sub_devices[i].subsystem, NULL);

	g_debug("udev_monitor_enable_receiving()");
	if (udev_monitor_enable_receiving(live_udev->udev_monitor)) {
		g_printerr("udev: monitor enable receiving failed");
		goto err_monitor_enable_receiving;
	}
	
	fd = udev_monitor_get_fd(live_udev->udev_monitor);
	udev_channel = g_io_channel_unix_new(fd);
	live_udev->source_id = g_io_add_watch(udev_channel, G_IO_IN, live_udev_monitor_device, live_udev->udev_monitor);
	g_debug("live_udev_enumerate_device()");
	if(live_udev_enumerate_device(live_udev->udev) < 0) {
		g_printerr("udev: failed to bind the udev monitor");
		goto err_udev_enumerate_device;
	}
	g_debug("live udev init finish");
	return 0;
	
err_udev_enumerate_device:
err_monitor_enable_receiving:
	udev_monitor_unref(live_udev->udev_monitor);
err_create_udev_monitor:
	udev_unref(live_udev->udev);
err_create_udev:
	g_free(live_udev);
	return -1;
}
