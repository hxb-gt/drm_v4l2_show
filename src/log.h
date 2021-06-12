#ifndef __LOG__
#define __LOG__

#include <stdio.h>
#include <glib.h>
#include <stdarg.h>

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

static inline void dbg_drm(const gchar *fmt, ...)	
{	
	#undef G_LOG_DOMAIN	
	#define G_LOG_DOMAIN "drm"	
	va_list args;
  	va_start (args, fmt);

	g_info(fmt, args);	
	va_end (args);
	
	#undef G_LOG_DOMAIN		
}

static inline void dbg_fbdev(const gchar *fmt, ...)	
{	
	#undef G_LOG_DOMAIN	
	#define G_LOG_DOMAIN "fbdev"	
	va_list args;
  	va_start (args, fmt);

	g_debug(fmt, args);	
	va_end (args);
	
	#undef G_LOG_DOMAIN		
}

static inline void dbg_v4l(const gchar *fmt, ...)	
{	
	#undef G_LOG_DOMAIN	
	#define G_LOG_DOMAIN "v4l2"	
	va_list args;
  	va_start (args, fmt);

	g_debug(fmt, args);	
	va_end (args);
	
	#undef G_LOG_DOMAIN		
}

static inline void dbg_usb(const gchar *fmt, ...)	
{	
	#undef G_LOG_DOMAIN	
	#define G_LOG_DOMAIN "usb"	
	va_list args;
  	va_start (args, fmt);

	g_debug(fmt, args);	
	va_end (args);
	
	#undef G_LOG_DOMAIN		
}

static inline void dbg_udev(const gchar *fmt, ...)	
{	
	#undef G_LOG_DOMAIN	
	#define G_LOG_DOMAIN "udev"	
	va_list args;
  	va_start (args, fmt);

	g_debug(fmt, args);	
	va_end (args);
	
	#undef G_LOG_DOMAIN		
}

static inline void dbg_func_line(void)	
{	
	#undef G_LOG_DOMAIN	
	#define G_LOG_DOMAIN "func_line"	
	
	g_debug("file %s: line %d (%s) reached",
		__FILE__, __LINE__, __func__);	
	
	#undef G_LOG_DOMAIN		
}


#if 0
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
#endif

#else


#define dbg_drm(fmt, args...)	
		
#define dbg_fbdev(fmt, args...)	

#define dbg_v4l(fmt, args...)	
				
#define dbg_usb(fmt, args...)	
				
#define dbg_udev(fmt, args...)	

#define dbg_func_line()	

#endif

#endif
