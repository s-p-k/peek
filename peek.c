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

	if (argc == 1)
		errx(1, "see %s -h", argv[0]);
	
	while ((opt = getopt(argc, argv, "hle:")) != -1) {
		switch(opt){
		case 'h':
			hflag = 1;
			usage();
			break;
		case 'e':
			eflag = 1;
			break;
		case 'l':
			listsheets(CHEATSHEET_DIR);			
			break;
		default:
			errx(1, "see %s -h", argv[0]);		
		}
	}

	if (argc == 2 && hflag == 0)
		readsheet(argv[1], "r");

/* open existing file for edit */

	if (eflag == 1)
		editsheet(argv[2]);

	return 0;
}
