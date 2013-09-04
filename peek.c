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

void
readonly(char *f);

int
filecopy(char *f);

void
usage(void)
{
	fprintf(stderr, "Usage: peek [-v][-e file][-h]\n");
	return;
}

int
main(int argc, char *argv[])
{
	char *envp, *filename;
	char ver[] = "0.1.1";
	int opt, fd;
	int eflag = 0;
	if (argc == 1) {
		fprintf(stderr, "Wrong usage: see %s -h\n", argv[0]);
		return 1;
	}
	
	if (argc == 2)
		readonly(argv[1]);

	while ((opt = getopt(argc, argv, "vhe:")) != -1){
		switch(opt){
		case 'v':
			printf("The current version: %s\n", ver);
			break;
		case 'h':
			usage();
			break;
		case 'e':
			eflag = 1;
			filename = optarg;
			break;
		default:
			usage();
			return 1;
		}
	}

	if (eflag == 1){
		if ((fd = open(filename, O_RDWR)) < 0)
			fprintf(stderr, "File %s does not exist\n", filename);
		envp = getenv("EDITOR");
			if (!envp){
			fprintf(stderr, "You must set your $EDITOR variable\n");
			return 1;
			} else {
			 (filecopy(filename) == 0) 
				printf("Copying was succesful\n");
			 /* open the copy of the file for edit */
			}
	}

	return 0;
}

/* open cheatsheet readonly */

void
readonly(char *f)
{
	FILE *fpoint;
	int fdesc;
	char bf[1000];
	
	fdesc = open(f, O_RDONLY);
	if (fdesc < 0) {
		fprintf(stderr, "file %s does not exist\n", f);
		return;
	} else {
		fpoint = fopen(f, "r");
		if (!fpoint)
			return;
	}

	while (fgets(bf,1000, fpoint) != NULL)
		printf("%s", bf);

	fclose(fpoint);
	return;
}

/* create a file copy before opening with $EDITOR */

int
filecopy(char *f)
{
	char ch;
	FILE *fp1, *fp2;

	fp1 = fopen(f, "r"); /* Create a copy of this file */
	fp2 = fopen("/tmp/backup.txt", "w");

	while (1) {
		ch = fgetc(fp1);
		if (ch != EOF)
			putc(ch, fp2);
		else
			break;
	}

	printf("File copied to /tmp/backup.txt\n");
	fclose(fp1);
	fclose(fp2);

	return 0;
}
