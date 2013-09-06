#ifndef _peek_h_
#define _peek_h_

#define CHEATSHEET_DIR = "/home/spk/.peek/"

void
usage(void)
{
	printf("Usage: peek [-h][-e file][file]\n");
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

#endif
