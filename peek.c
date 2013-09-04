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

void
usage(void)
{
	fprintf(stderr, "Usage: peek [-v][-r file][-h]\n");
	return;
}

int
main(int argc, char *argv[])
{
	char *envp;
	char ver[] = "0.1.1";
	int opt;
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
			break;
		default:
			usage();
			return 1;
		}
	}

	if (eflag == 1){
		envp = getenv("EDITOR");
		if (!envp)
			fprintf(stderr, "You must set your $EDITOR variable\n");
	}

	return 0;
}

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
