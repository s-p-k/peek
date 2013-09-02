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
	fprintf(stderr, "Usage: peek [-v][-f file][-h]\n");
	return;
}

int
main(int argc, char **argv)
{
	
	struct stat buffer;
	char ver[] = "0.1.1";
	int opt, status;
	int fflag = 0;
	int hflag = 0;
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
		case 'f':
			fflag = 1;
			filename = optarg;
			printf("the filename was %s\n", filename);
			break;
		case 'h':
			hflag = 1;
			usage();
			break;
		case 'e':
			filename = optarg;
			printf("You have chosen to edit file %s\n", filename);
			break;
		default:
			usage();
			return 1;
		}

	}
		
	if (hflag == 0 && status != 0)
		fprintf(stderr, "file %s does not exist\n", filename);

	status = stat(filename, &buffer);
	
	if (fflag == 1 && status ==0)
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

	return 0;
}
