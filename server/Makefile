include ../../Make.defines

CFLAGS = -I../../lib -g -O2 -D_REENTRANT -Wall
LIBS = ../../libunp.a -lpthread
LIBS_XTI = ../../libunpxti.a ../../libunp.a -lpthread

PROGS =	server

all:	${PROGS}

server:	server.o str_echo08.o sigchldwaitpid.o
		${CC} ${CFLAGS} -o $@ server.o str_echo08.o sigchldwaitpid.o \
			${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
