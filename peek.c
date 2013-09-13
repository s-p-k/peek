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

void readSheet(char *f);

void editSheet(char *f);

void createSheet(char *f);

void listSheet(char *dr);

void
usage(void)
{
	printf("Usage: peek [-h] [-l] [-e file] [file]\n");
}

int
main(int argc, char *argv[])
{
	int opt;
	int hflag = 0, eflag = 0, lflag = 0;

	if (argc)
		usage();
	
	while ((opt = getopt(argc, argv, "hle:")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		case 'e':
			eflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		default:
			errx(1, "see %s -h", argv[0]);		
		}
	}

	if (hflag)
		usage();
	if (lflag)
		listSheet(CHEATSHEET_DIR);
	if (eflag)
		editSheet(argv[2]);
	if (argc == 2 && hflag == 0 && eflag == 0 && lflag == 0)
		readSheet(argv[1]);

	return 0;
}

void
readSheet(char *f)
{
	int c;
	FILE *fpoint;
	char readfile[PATH_MAX] = CHEATSHEET_DIR;

	strncat(readfile, f, sizeof(readfile) - strlen(readfile) - 1);
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
	char file[PATH_MAX] = CHEATSHEET_DIR;
	char *EDITOR, *BIN_NAME;

	EDITOR = getenv("EDITOR");
	if (!EDITOR) {
		EDITOR = "/usr/bin/vi";
		BIN_NAME = "vi";
	}

	BIN_NAME = strrchr(EDITOR, '/');
	BIN_NAME = strrchr(EDITOR, BIN_NAME[1]);
	
	strncat(file, f, sizeof(file) - strlen(file) - 1);
	ret = execl(EDITOR, BIN_NAME, file, (char *)0);
	if (ret == -1)
		err(1, "editSheet: configure peek.c correctly\n");

	return;
}

void
listSheet(char *dr)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(dr);
	if (!d)
		err(1, "listSheet: %s", dr);
	printf("Available cheatsheets:\n");
	while ((dir = readdir(d)) != NULL)
		if (!strcmp(dir->d_name, ".") || !(strcmp(dir->d_name, "..")))
			continue;
		else
			printf("%s\n", dir->d_name);
	closedir(d);

	return;
}
