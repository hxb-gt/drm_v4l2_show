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

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
				Makefile
				src/Makefile
				lib/Makefile
				])
AC_OUTPUT
