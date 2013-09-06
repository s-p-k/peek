#ifndef _peek_h_
#define _peek_h_

#define CHEATSHEET_DIR "/home/spk/.peek/"

#define TMP_DIR "/tmp/"

void
usage(void)
{
	printf("Usage: peek [-h][-l][-e file][file]\n");
	printf("see also the peek man page\n");
	return;
}

int
openfile(char *f, char *mode)
{
	int c;
	FILE *fpoint;
	
	fpoint = fopen(f, mode);

	if (!fpoint)
		err(1, "%s", f);

	if ((strcmp(mode, "r")) == 0)
		while((c = fgetc(fpoint)) != EOF)
			printf("%c", c);

	if ((strcmp(mode, "r+")) == 0)
		printf("Open the file for edit\n");

	fclose(fpoint);

	return 0;
}

/* Create a new cheatsheet: used for the -c option */
void
createcheatsheet(char *f)
{
	char newfile[50] = CHEATSHEET_DIR;
	strcat(newfile, f);
	printf("You want to create file %s\n", newfile);
	
	return;
}
	
/* list cheatsheets in CHEATSHEET_DIR */
/* must make the printing prettier */

void
listcheatsheets(char *dr)
{
	DIR *d;
	struct dirent *dir;
	
	d = opendir(dr);

	if (!d)
		err(1, "yo mate! %s", dr);

	while ((dir = readdir(d)) != NULL)
		printf("%s ", dir->d_name);

	printf("\n");

	closedir(d);

	return;
}

/* creates a copy of a cheatsheet, before opening it for edit with -e option */

void
makecopy(char *f)
{
	int ch;
	FILE *fp1, *fp2;

	fp1 = fopen(f, "r"); /* original file */

	/* need to make the fp2 file look like: /tmp/cheatsheet_name.peek */
	fp2 = fopen("TMP_DIR/f/backup/", "w"); /* backup file in /tmp */

	while (1) {
		ch = fgetc(fp1);

		if (ch == EOF)
			break;
		else
			putc(ch, fp2);
	}

	fclose(fp1);
	fclose(fp2);
}

#endif
