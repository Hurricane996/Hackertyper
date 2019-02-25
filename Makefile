PREFIX=/usr/local
EXEC_PREFIX=$(PREFIX)/bin
DATAROOTDIR=$(PREFIX)/share
DATADIR=$(DATAROOTDIR)
MAN1DIR=$(DATAROOTDIR)/man/man1

CFLAGS=-Wall -pedantic -std=c99
LDFLAGS=-lncurses

all: hackertyper

clean:
	rm -f hackertyper{,.o,.h}
install: hackertyper
	install hackertyper $(EXEC_PREFIX) -m755
	install hackertyper.txt $(DATADIR) -m644
	install hackertyper.1   $(MAN1DIR) -m644
hackertyper: hackertyper.o
hackertyper.o:hackertyper.c
hackertyper.c: hackertyper.h
hackertyper.h: hackertyper.h.in
	sed "s@%datadir%@$(DATADIR)@g" hackertyper.h.in > hackertyper.h
