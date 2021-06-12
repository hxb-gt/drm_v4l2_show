#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([drm_v4l2_demo], [1.0.0], [huangxiaobo@brigates.com],,[hxb-gt])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_SRCDIR([src])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER(stdio.h,
				AC_DEFINE(HAVE_STDIO_H, 1, 
				[DEFINE to 1 if you have <stdio.h>.]), 
				[AC_MSG_ERROR([sorry, can't do anything for you])])
				
AC_CHECK_HEADER(getopt.h,
				AC_DEFINE(HAVE_GETOPT_H, 1, 
				[Define to 1 if you have the <getopt.h> header file.]), 
				[AC_MSG_ERROR([sorry, can't do anything for you])])


# Checks for typedefs, structures, and compiler characteristics.
AC_DEFINE([COPYRIGHT_YEAR], [m4_esyscmd([date +%Y])], [year in copyright message])

# Checks for library functions.
#AC_CHECK_LIB([glib-2.0], [main],, [AC_MSG_ERROR([glib library is missing])])
#AC_CHECK_LIB([udev], [udev_new], [], [AC_MSG_ERROR([udev library is missing])])
#AC_CHECK_LIB([drm], [main], [], [AC_MSG_ERROR([drm library is missing])])

PKG_CHECK_MODULES([LIBUDEV], [libudev >= 199])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.22.0 gobject-2.0 >= 2.22.0 gio-2.0])

# Options for build
AC_ARG_ENABLE([v4l2todrm], 
			AS_HELP_STRING([--enable-v4l2todrm], 
							[enable data from v4l2 to drm show]),
							AC_SUBST([v4l2todrm], [yes]))
AC_ARG_ENABLE([debug], 
			AS_HELP_STRING([--enable-debug], 
							[Enable debug informations (default: Not enabled)]),
							AC_DEFINE([DEBUG], 1,
							[DEFINE to 1 if you have debug program.]))
AC_ARG_ENABLE([fbdev], 
			AS_HELP_STRING([--disable-fbdev], 
							[enable fbdev subsystem (default: disabled)]),
							[fbdev=no])
AS_IF([test xno != "x$fbdev"],
	AC_DEFINE([FBDEV], 1, [DEFINE to 1 if you have use fbdev subsystem.]))



AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
				Makefile
				src/Makefile
				lib/Makefile
				])
AC_OUTPUT
