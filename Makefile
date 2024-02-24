CC=gcc
CFLAGS=-O2 -Wall

.PHONY : clean install uninstall

0sv: main.o
	${CC} ${CFLAGS} $^ -o $@

.c.o:
	${CC} ${FLAGS} -c $<

clean:
	@rm -rf 0sv *.o

install: 0sv
	cp 0sv 0awk /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/0sv /usr/local/bin/0awk
