/* 
 * A simple program to add, edit and read
 * your cheatsheets.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int openfile(char *f, char *md);

void
usage(void)
{
	printf("Usage: peek [file][-e file][-h]\n");
	return;
}

int
main(int argc, char *argv[])
{
	int opt;
	int eflag = 0, hflag = 0;

	if (argc == 1) {
		fprintf(stderr, "Wrong usage: see %s -h\n", argv[0]);
		exit (1);
	}
	
	while ((opt = getopt(argc, argv, "he:")) != -1) {
		switch(opt){
		case 'h':
			hflag = 1;
			usage();
			break;
		case 'e':
			eflag = 1;
			break;
		default:
			usage();
			exit (1);
		}
	}

	if (argc == 2 && hflag == 0)
		openfile(argv[1], "r");

/* open existing file for edit */

	if (eflag == 1)
		openfile(argv[2], "r+");

	return 0;
}

int
openfile(char *f, char *md)
{
	int c;
	FILE *fpoint;
	int comp;

	fpoint = fopen(f, md);

	if (!fpoint) {
		perror("openfile");
		exit (1);
	}

	if ((comp = strcmp(md, "r")) == 0) {
	    while((c = fgetc(fpoint)) != EOF)
		    printf("%c", c);
	} else if ((comp = strcmp(md, "r+")) == 0) {
		printf("Open the file for edit\n");
	}

	fclose(fpoint);

	return 0;
}
