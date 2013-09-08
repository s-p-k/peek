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
#include <limits.h>

#define CHEATSHEET_DIR "/home/spk/.peek/"
#define EDITOR "/usr/bin/mg"
#define BIN_NAME "mg"

void
usage(void)
{
	printf("Usage: peek [-h][-l][-e file][file]\n");
}

void readSheet(char *f);

void editSheet(char *f);

void createSheet(char *f);

void listSheet(char *dr);

int
main(int argc, char *argv[])
{
	
	int opt;
	int eflag = 0, hflag = 0;

	if (argc == 1)
		usage();
	
	while ((opt = getopt(argc, argv, "hle:")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			usage();
			break;
		case 'e':
			eflag = 1;
			break;
		case 'l':
			listSheet(CHEATSHEET_DIR);			
			break;
		default:
			errx(1, "see %s -h", argv[0]);		
		}
	}

	if (argc == 2 && hflag == 0)
		readSheet(argv[1]);

/* open existing file for edit */
	if (eflag == 1)
		editSheet(argv[2]);

	return 0;
}

void
readSheet(char *f)
{
	int c, max;
	FILE *fpoint;
	char readfile[PATH_MAX] = CHEATSHEET_DIR;

	max = sizeof(PATH_MAX) + sizeof(CHEATSHEET_DIR) + sizeof(f);
	strncat(readfile, f, max - 1);
	fpoint = fopen(readfile, "r");

	if (!fpoint)
		err(1, "readSheet %s", f);

	while((c = fgetc(fpoint)) != EOF)
		printf("%c", c);
	
	fclose(fpoint);

	return;
}
	
void
editSheet(char *f)
{

	int ret;
	FILE *fpoint;
	char file[PATH_MAX] = CHEATSHEET_DIR;

	strcat(file, f);
	fpoint = fopen(file, "a+");

	if (!fpoint)
		err(1, "editsheet %s", f);

	ret = execl(EDITOR, BIN_NAME, file, (char *)0);

	if (ret == -1)
		err(1, "editsheet: check in peek.h if all variables are set\n");

	fclose(fpoint);

	return;
}

/* Create a new cheatsheet */

void
createSheet(char *f)
{
	FILE *fpoint;
	char newfile[PATH_MAX] = CHEATSHEET_DIR;

	strcat(newfile, f);
	fpoint = fopen(newfile, "wx");

	if (!fpoint)
		err(1, "YOOOOO %s", newfile);

	fclose(fpoint);

	return;
}

/* list cheatsheets in CHEATSHEET_DIR: must make the printing prettier
 * and fix the error when done listing
 */

void
listSheet(char *dr)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(dr);

	if (!d)
		err(1, "listsheets %s", dr);

	printf("Available cheatsheets:\n");

	while ((dir = readdir(d)) != NULL)
		printf("%s\n", dir->d_name);

	closedir(d);

	return;
}
