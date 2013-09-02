/* A simple program to add, edit and read
 * your cheatsheets.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void usage(void);

int
main(int argc, char **argv)
{
	
	struct stat buffer;
	char ver[] = "0.1.1";
	int opt, status;
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
	status = stat(filename, &buffer);

	if (status != 0)
	{
		fprintf(stderr, "file %s does not exist\n", filename);
	}
	else
	{
		/* Here I should write the code according to the other options
		 * passed to peek. If it's -e, then the filename will be opened
		 * for edit. I must also fix the arguments so that I have behaviour
		 * like this: 
		 *
		 * $ ./peek tar # this should search for a tar cheatsheet, if it
		 * doesn't exist, if EDITOR env variable is set, open that file
		 * with it.
		 *
		 * $ ./peek -e tar # should edit the tar cheatsheet.
		 * A cheatsheet dir variable must also be declared, so that the
		 * program will seek for cheatsheets in that directory.
		 */
       
		printf("File exists\n");
	}

	return 0;
}

/* must update usage functions to inform the user for all the possible options. */

void
usage(void)
{
	printf("Usage: peek [-v][-f file][-h]\n");
	return;
}
