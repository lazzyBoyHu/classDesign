include ../../Make.defines

CFLAGS = -I../../lib -g -O2 -D_REENTRANT -Wall
LIBS = ../../libunp.a -lpthread
LIBS_XTI = ../../libunpxti.a ../../libunp.a -lpthread

PROGS =	terminal_main

all:	${PROGS}

terminal_main:	terminal_main.o terminal.o
		${CC} ${CFLAGS} -o $@ terminal_main.o terminal.o \
			${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
