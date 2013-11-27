BIN = peek
SRC = peek.c
OBJ = ${SRC:.c=.o}


PREFIX = /usr
MANDIR = /share/man/man1
MANDST = ${PREFIX}${MANDIR}

CC = gcc

CFLAGS += -Wall -Wextra

$(BIN): ${OBJ}
	 ${CC} ${CFLAGS} -o $@ ${OBJ}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	rm -rf ${BIN} ${OBJ}

install:
	cp -f ${BIN} ${PREFIX}/bin/
	chmod 755 ${PREFIX}/bin/${BIN}
	mkdir -p ${MANDST}
	gzip -c peek.1 > peek.1.gz
	mv -f peek.1.gz /usr/share/man/man1/
	chmod 644 /usr/share/man/man1/peek.1.gz

uninstall:
	rm -f ${PREFIX}/bin/${BIN}
	rm -f ${MANDST}/peek.1.gz

.PHONY: install uninstall clean
