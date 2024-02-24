CC=gcc
CFLAGS=-O2 -Wall

.PHONY : clean

0sv: main.o
	${CC} ${CFLAGS} $^ -o $@

.c.o:
	${CC} ${FLAGS} -c $<

clean:
	@rm -rf *.exe *.o

