PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
DATAROOTDIR=$(PREFIX)/share
DATADIR=$(DATAROOTDIR)
MAN1DIR=$(DATAROOTDIR)/man/man1

CFLAGS=-Wall -pedantic -std=c99
LDFLAGS=-lncurses

all: hackertyper

.PHONY: all hackertyper clean install

hackertyper: hackertyper.o
	cc -o $@ $^ $(LDFLAGS)
hackertyper.o: src/hackertyper.c
	cc -c $(CFLAGS) -o $@ $^
src/hackertyper.c: src/hackertyper.h
src/hackertyper.h:src/hackertyper.h.in
	sed "s@%datadir%@$(DATADIR)@g" src/hackertyper.h.in > src/hackertyper.h

clean:
	rm -f hackertyper{,.o} src/hackertyper.h

install:
	install -D -m644 data/hackertyper.txt $(DATADIR)/hackertyper.txt
	install -D -m644 man/hackertyper.1 $(MAN1DIR)/hackertyper.1
	install -D -m755 hackertyper $(BINDIR)/hackertyper
