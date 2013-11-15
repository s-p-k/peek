--------------------------------------------------------------------------------
peek 
--------------------------------------------------------------------------------

Peek is a simple cheatsheet handler.

Configuring peek:

1. peek used by default your $EDITOR, if $EDITOR is not set, it uses /usr/bin/vi

	CHEATSHEETDIR "/home/your-user/.peek/"

make sure ~/.peek exists.

2. I will soon add a Makefile, until then just build with gcc with something
like:

gcc -Wall -Wextra peek.c -o peek

3. You can get a sample of cheatheets here:

https://github.com/s-p-k/cheatsheets

Just copy them on your ~/.peek/ directory.

________________________________________________________________________________
Screenshots
________________________________________________________________________________

Listing available cheatsheets in ~/.peek/:

![alt tag](https://github.com/s-p-k/peek/blob/master/list-cs.png)