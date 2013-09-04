/* 
 * A simple program to add, edit and read
 * your cheatsheets.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
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

	char ver[] = "0.1.1";
	int opt;

	if (argc == 1) {
		fprintf(stderr, "Wrong usage: see %s -h\n", argv[0]);
		return 1;
	}
	
	if (argc == 2)
		readonly(argv[1]);

	while ((opt = getopt(argc, argv, "vh")) != -1){
		switch(opt){
		case 'v':
			printf("The current version: %s\n", ver);
			break;
		case 'h':
			usage();
			break;
		default:
			usage();
			return 1;
		}
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
