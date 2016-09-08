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
#include <libgen.h>

#include "config.h"

static void readSheet(char *f);

static void editSheet(char *f);

static void listSheet(char *dr);

static void
usage(void)
{
	printf("Usage: peek [-h] [-e file] [file]\n");
}

int
main(int argc, char *argv[])
{
	int opt;
	int hflag = 0, eflag = 0, lflag = 0;

	if (argc == 1)
		listSheet(CHEATSHEET_DIR);

	while ((opt = getopt(argc, argv, "he:")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		case 'e':
			eflag = 1;
			break;
		default:
			errx(1, "see %s -h", argv[0]);		
		}
	}

	if (hflag)
		usage();
	if (eflag)
		editSheet(argv[2]);
	if (argc == 2 && hflag == 0 && eflag == 0 && lflag == 0)
		readSheet(argv[1]);

	return 0;
}

static void
readSheet(char *f)
{
	int c;
	FILE *fpoint = NULL;
	char readfile[PATH_MAX] = CHEATSHEET_DIR;

	strncat(readfile, f, sizeof(readfile) - strlen(readfile) - 1);
	fpoint = fopen(readfile, "r");
	if (!fpoint)
		err(1, "readSheet %s", f);
	while((c = fgetc(fpoint)) != EOF)
		printf("%c", c);
	(void) fclose(fpoint);
	printf("\n");

	return;
}
	
static void
editSheet(char *f)
{
	int ret;
	char *editor, *bin_name;
	char file[PATH_MAX] = CHEATSHEET_DIR;

	editor = getenv("EDITOR");
	if (!editor)
		editor = "/bin/vi";
	bin_name = basename(editor);
	strncat(file, f, sizeof(file) - strlen(file) - 1);
	ret = execl(editor, bin_name, file, (char *)0);
	if (ret == -1)
		err(1, "editSheet: configure peek.c correctly\n");

	return;
}

static void
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
	(void) closedir(d);

	return;
}
