#AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = drm_v4l2_demo
drm_v4l2_demo_SOURCES = main.c arg_parse.c 
BUILT_SOURCES = $(top_srcdir)/lib/libdrmv4l2demo.a
drm_v4l2_demo_LDADD = $(top_srcdir)/lib/libdrmv4l2demo.a

AM_CPPFLAGS = -I$(top_srcdir)/lib