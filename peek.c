/* 
 * A simple program to add, edit and read
 * your cheatsheets.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define DEF_DIR "/home/spk/repos/c/peek/csdir"

void
usage(void)
{
	fprintf(stderr, "Usage: peek [-v][-f file][-h]\n");
	return;
}

int
main(int argc, char *argv[])
{
	
	struct stat buffer;
	char ver[] = "0.1.1";
	int opt, status;
	int hflag = 0;
	int eflag = 0;

	/* the cheatsheet to be read, edited or created */
	const char *filename = "unspecified"; 
	
	if (argc == 1)
	{
		fprintf(stderr, "Wrong usage: see %s -h\n", argv[0]);
		return 1;
	}
	
	while ((opt = getopt(argc, argv, "vhf:e:")) != -1)
	{
		switch(opt)
		{
		case 'v':
			printf("The current version: %s\n", ver);
			break;
		case 'h':
			hflag = 1;
			usage();
			break;
		case 'e':
			filename = optarg;
			eflag = 1;
			printf("You have chosen to edit file %s\n", filename);
			break;
		default:
			usage();
			return 1;
		}

	}

	status = stat(filename, &buffer);
	
	if (argc == 2)
	{
		filename = argv[1];
		status = stat(filename, &buffer);
		if (status == 0)
			printf("Here we should open the file in argv[1]");
	}
	
	if (hflag == 0 && (status = stat(filename, &buffer) != 0))
		fprintf(stderr, "file %s does not exist\n", filename);

	if (eflag == 1)
		printf("Open file indicated from -e option\n");

	return 0;
}
