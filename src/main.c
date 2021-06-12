#include <stdio.h>
#include "config.h"
#include "arg_parse.h"
#include "fbdev.h"

int main(int argc, char *argv[])
{

	parse_args(argc, argv);

	fbdev_init();
	
	return 0;	
}
