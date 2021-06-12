#AUTOMAKE_OPTIONS = subdir-objects

LDLIBS = $(LIBS)

bin_PROGRAMS = drm_v4l2_demo
drm_v4l2_demo_SOURCES = main.c log.c log.h arg_parse.c arg_parse.h 

#fbdev subsystem
drm_v4l2_demo_SOURCES += fbdev_init.c fbdev.h

drm_v4l2_demo_LDADD = $(top_srcdir)/lib/libdrmv4l2demo.a

AM_CPPFLAGS = -I$(top_srcdir)/lib