/* 
 * A simple program to add, edit and read
 * your cheatsheets.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <dirent.h>

#include "peek.h"

int
main(int argc, char *argv[])
{
	
	int opt;
	int eflag = 0, hflag = 0;
	char *cheatsheet;

	if (argc == 1)
		errx(1, "see %s -h", argv[0]);
	
	while ((opt = getopt(argc, argv, "hc:e:l")) != -1) {
		switch(opt){
		case 'h':
			hflag = 1;
			usage();
			break;
		case 'c':
			cheatsheet = optarg;
			createcheatsheet(cheatsheet);
			break;
		case 'e':
			eflag = 1;
			break;
		case 'l':
			listcheatsheets(CHEATSHEET_DIR);			
			break;
		default:
			errx(1, "see %s -h", argv[0]);		
		}
	}

	if (argc == 2 && hflag == 0)
		openfile(argv[1], "r");

/* open existing file for edit */

	if (eflag == 1)
		openfile(argv[2], "r+");

	return 0;
}
