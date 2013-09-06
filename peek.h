#ifndef _peek_h_
#define _peek_h_

#define CHEATSHEET_DIR "/home/spk/.peek/"

void
usage(void)
{
	printf("Usage: peek [-h][-l][-e file][file]\n");
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

/* list cheatsheets in CHEATSHEET_DIR */

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

#endif
