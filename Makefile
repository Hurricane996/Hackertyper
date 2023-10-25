PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
DATAROOTDIR=$(PREFIX)/share
DATADIR=$(DATAROOTDIR)
MAN1DIR=$(DATAROOTDIR)/man/man1


CFLAGS=-Wall -pedantic -std=c99 -O3 -DDATADIR=\"$(DATADIR)\"
LDFLAGS=-lncurses

all: hackertyper

.PHONY: all clean install

hackertyper: hackertyper.o
	cc -o $@ $^ $(LDFLAGS)
hackertyper.o: src/hackertyper.c
	cc -c $(CFLAGS) -o $@ $^
src/hackertyper.c: src/hackertyper.h


clean:
	rm -f hackertyper{,.o}

install:
	install -D -m644 data/hackertyper.txt $(DATADIR)/hackertyper.txt
	install -D -m644 man/hackertyper.1 $(MAN1DIR)/hackertyper.1
	install -D -m755 hackertyper $(BINDIR)/hackertyper
