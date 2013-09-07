#ifndef _peek_h_
#define _peek_h_

#define CHEATSHEET_DIR "/home/spk/.peek/"
#define EDITOR "/usr/bin/mg"
#define BIN_NAME "mg"

void
usage(void)
{
	printf("Usage: peek [-h][-l][-e file][file]\n");
	printf("see also the peek man page\n");
	
	return;
}

int
readsheet(char *f, char *mode)
{
	int c;
	FILE *fpoint;
	char readfile[100] = CHEATSHEET_DIR;
	
	strcat(readfile, f);

	fpoint = fopen(readfile, mode);

	if (!fpoint)
		err(1, "%s", f);

	if ((strcmp(mode, "r")) == 0)
		while((c = fgetc(fpoint)) != EOF)
			printf("%c", c);
	
	fclose(fpoint);

	return 0;
}

void
editsheet(char *f)
{
	int ret;
	FILE *fpoint;
	char file[100] = CHEATSHEET_DIR;
	
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
createsheet(char *f)
{
	FILE *fpoint;
	char newfile[50] = CHEATSHEET_DIR;

	strcat(newfile, f);
	
	fpoint = fopen(newfile, "wx");

	if (!fpoint)
		err(1, "YOOOOO %s", newfile);

	fclose(fpoint);
	
	return;
}
	
/* list cheatsheets in CHEATSHEET_DIR */
/* must make the printing prettier */

void
listsheets(char *dr)
{
	DIR *d;
	struct dirent *dir;
	
	d = opendir(dr);

	if (!d)
		err(1, "listsheets %s", dr);

	printf("Available cheatsheets:\n");

	while ((dir = readdir(d)) != NULL)
		printf("%s ", dir->d_name);

	printf("\n");

	closedir(d);

	return;
}

#endif
