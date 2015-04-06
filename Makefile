BIN = peek
SRC = peek.c
OBJ = ${SRC:.c=.o}

VERSION = 0.1

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

CC = gcc
CFLAGS += -Wall -Wextra

$(BIN): ${OBJ}
	${CC} ${CFLAGS} -o $@ ${OBJ}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	@echo cleaning
	@rm -rf ${BIN} ${OBJ} peek-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p peek-${VERSION}
	@cp -R LICENSE Makefile config.h README peek.1 ${SRC} \
		peek-${VERSION}
	@tar -cf peek-${VERSION}.tar peek-${VERSION}
	@gzip peek-${VERSION}.tar
	@rm -rf peek-${VERSION}


install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f peek ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/peek
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < peek.1 > ${DESTDIR}${MANPREFIX}/man1/peek.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/peek.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/peek
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/peek.1

.PHONY: all options clean dist install uninstall
