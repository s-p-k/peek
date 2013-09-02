/* A simple program to add, edit and read
 * your cheatsheets.
 */

#include <stdio.h>
#include <unistd.h>

void usage(void);

int
main(int argc, char **argv)
{

	char ver[] = "0.1.1";
	int opt;
	/* the cheatsheet to be read, edited or created */
	const char *filename = "unspecified"; 
	
	if (argc <= 1)
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
		case 'f':
			filename = optarg;
			printf("the filename was %s\n", filename);
			break;

		case 'h':
			usage();
			break;
		case 'e':
			filename = optarg;
			printf("You have chosen to edit file %s\n", filename);
			break;
		default:
			fprintf(stderr, "Usage: %s [-v][-f file]\n", argv[0]);
			return 1;
		}

	}
	
	return 0;
}

void
usage(void)
{
	printf("Usage: peek [-v][-f file][-h]\n");
	return;
}
