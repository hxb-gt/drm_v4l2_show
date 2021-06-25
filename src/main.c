#include <stdio.h>
#include <glib.h>

#include "config.h"
#include "arg_parse.h"
#include "fbdev.h"
#include "live_udev.h"

int main(int argc, char *argv[])
{
	GMainLoop *loop;
		
	parse_args(argc, argv);

//	fbdev_init();

	loop = g_main_loop_new(NULL, FALSE);

	live_udev_init();

	g_main_loop_run(loop);
	
	return 0;	
}
