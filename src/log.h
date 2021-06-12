#ifndef __LOG__
#define __LOG__

#include <stdio.h>
#include "config.h"
#include "misc.h"

enum debug_level {
	DBG_DRM = 0,
	DBG_FBDEV,
	DBG_V4L2,
	DBG_USB,
	DBG_UDEV
};

extern int log_level;
int debug_level_parse(char *args);

#ifdef DEBUG

#define dbg_drm(fmt, args...)	\
	if (log_level & BIT(DBG_DRM)) \
		printf("Drm:" fmt, ## args)
		
#define dbg_fbdev(fmt, args...)	\
	if (log_level & BIT(DBG_FBDEV)) \
		printf("Fbdev:" fmt, ## args)

#define dbg_v4l(fmt, args...)	\
	if (log_level & BIT(DBG_V4L2)) \
		printf("V4l:" fmt, ## args)
		
#define dbg_usb(fmt, args...)	\
	if (log_level & BIT(DBG_USB)) \
		printf("Usb:" fmt, ## args)
				
#define dbg_udev(fmt, args...)	\
	if (log_level & BIT(DBG_UDEV)) \
		printf("Udev:" fmt, ## args)
		
#define dbg_func_line()	\
	printf("At:%s.%s.%s()",__FILE__, __LINE__, __func__)

#else


#define dbg_drm(fmt, args...)	
		
#define dbg_drm(fmt, args...)	

#define dbg_drm(fmt, args...)	
				
#define dbg_drm(fmt, args...)	
				
#define dbg_drm(fmt, args...)	

#define dbg_func_line()	

#endif

#endif
