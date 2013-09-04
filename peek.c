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
usage(void)
{
	fprintf(stderr, "Usage: peek [-v][-r file][-h]\n");
	return;
}

int
main(int argc, char *argv[])
{

	char ver[] = "0.1.1";
	char *filename;
	char buf[1000];
	int opt, fd;
	int rflag = 0;
	FILE *fp;
	
	if (argc == 1) {
		fprintf(stderr, "Wrong usage: see %s -h\n", argv[0]);
		return 1;
	}
	
	while ((opt = getopt(argc, argv, "vhr:")) != -1){
		switch(opt){
		case 'v':
			printf("The current version: %s\n", ver);
			break;
		case 'h':
			usage();
			break;
		case 'r':
			filename = optarg;
			rflag = 1;
			break;
		default:
			usage();
			return 1;
		}

	}

	if (rflag == 1) {
		fd = open(filename, O_RDONLY);
		if (fd < 0) {
			fprintf(stderr, "file %s does not exist\n", filename);
			return 1;
		} else {
			fp = fopen(filename, "r");
			if (!fp)
				return 1;
		}
		while (fgets(buf,1000, fp) != NULL)
			printf("%s", buf);
		
		fclose(fp);
	}

	return 0;
}
