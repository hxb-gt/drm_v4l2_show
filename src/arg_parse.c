#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "progname.h"
#include "log.h"

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

static const struct option longopts[] = {
  {"help", no_argument, NULL, 'h'},
  {"debug", required_argument, NULL, 'd'},
  {"version", no_argument, NULL, 'v'},
  {NULL, 0, NULL, 0}
};

static const char *optstring = "hd:v";

static void print_help (void);
static void print_version (void);

void parse_args(int argc, char *argv[])
{
	int opts;
	extern char *optarg;
	extern int optind, optopt;

	set_program_name(argv[0]);
	
#if HAVE_GETOPT_H
	while((opts = getopt_long(argc, argv, optstring, longopts, NULL)) != -1) {
#else
	while ((opts = getopt(argc, argv, optstring)) != -1) {
#endif
		switch(opts) {
		case 'h':
			print_help();
			break;
		case 'd':
			if(debug_level_parse(optarg)) {
				print_help();
				exit(-1);
			}
			break;
		case 'v':
			print_version();
			break;
		case ':':
			printf("opttion %c must have a parameter\n", (uint8_t)optopt);
			print_help();
			exit(-1);
		case '?':
			printf("opttion %c is incognizant\n", (uint8_t)optopt);
			print_help();
			exit(-1);
		default:
			break;
		}
	}
}

static void
print_help (void)
{
  /* TRANSLATORS: --help output 1 (synopsis)
     no-wrap */
  printf (("\
Usage: %s [OPTION]...\n"), program_name);

  /* TRANSLATORS: --help output 2 (brief description)
     no-wrap */
  fputs (("\
Print a friendly, customizable greeting.\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output 3: options 1/2
     no-wrap */
  fputs (("\
  -h, --help          display this help and exit\n\
  -v, --version       display version information and exit\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output 4: options 2/2
     no-wrap */
  fputs (("\
  -t, --traditional       use traditional greeting\n\
  -n, --next-generation   use next-generation greeting\n\
  -g, --greeting=TEXT     use TEXT as the greeting message\n"), stdout);

  printf ("\n");
  /* TRANSLATORS: --help output 5+ (reports)
     TRANSLATORS: the placeholder indicates the bug-reporting address
     for this application.  Please add _another line_ with the
     address for translation bugs.
     no-wrap */
  printf (("\
Report bugs to: %s\n"), PACKAGE_BUGREPORT);
#ifdef PACKAGE_PACKAGER_BUG_REPORTS
  printf (("Report %s bugs to: %s\n"), PACKAGE_PACKAGER,
	  PACKAGE_PACKAGER_BUG_REPORTS);
#endif
#ifdef PACKAGE_URL
  printf (("%s home page: <%s>\n"), PACKAGE_NAME, PACKAGE_URL);
#else
  printf (("%s home page: <http://www.gnu.org/software/%s/>\n"),
	  PACKAGE_NAME, PACKAGE);
#endif
  fputs (("General help using GNU software: <http://www.gnu.org/gethelp/>\n"),
	 stdout);
}

/* Print version and copyright information.  */

static void
print_version (void)
{
  printf ("%s (%s) %s\n", PACKAGE, PACKAGE_NAME, VERSION);
  /* xgettext: no-wrap */
  puts ("");

  /* It is important to separate the year from the rest of the message,
     as done here, to avoid having to retranslate the message when a new
     year comes around.  */
  printf (("\
Copyright (C) %d Free Software Foundation, Inc.\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n"), COPYRIGHT_YEAR);
}

