#include <string.h>
#include "log.h"

int log_level;

int debug_level_parse(char *args)
{
	if (args == NULL)
		return -1;
	
	if (strcmp(args, "drm") == 0) {
		log_level |= (1 << DBG_DRM);
		return 0;
	} else if (strcmp(args, "fbdev") == 0) {
		log_level |= (1 << DBG_FBDEV);
		return 0;
	} else if (strcmp(args, "v4l") == 0) {
		log_level |= (1 << DBG_V4L2);
		return 0;
	} else if (strcmp(args, "usb") == 0) {
		log_level |= (1 << DBG_USB);
		return 0;
	} else if (strcmp(args, "udev") == 0) {
		log_level |= (1 << DBG_UDEV);
		return 0;
	}
	
	return -1;
}

