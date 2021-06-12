#ifndef __FBDEV__
#define __FBDEV__

#include "config.h"

#ifdef FBDEV
int fbdev_init();

#else

int fbdev_init()	 {	}

#endif

#endif

