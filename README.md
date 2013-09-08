peek 
--------------------------------------------------------------------------------

Peek is a simple cheatsheet handler.

Configuring peek:

1. Supposing you want to configure peek with mg, open peek.c with your
favourite editor and make the following changes:


	CHEATSHEETDIR "/home/your-user/.peek/"

	EDITOR "/usr/bin/mg"

	BIN_NAME "mg"

If you want to use vim instead, replace mg with vim and make sure ~/.peek
exists.

2. Save it.

3. I will soon add a Makefile, until then just build with gcc with something
like:

```gcc -Wall -Wextra -Wunused peek.c -o peek```
