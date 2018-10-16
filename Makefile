SHELL=/bin/sh
CFLAGS=-Wall -Wextra --pedantic -g -std=c99

prefix=/usr/local
exec_prefix=$(prefix)

bindir=$(exec_prefix)/bin

datarootdir=$(prefix)/share
mandir=$(datarootdir)/man
man1dir=$(mandir)/man1

data_file=data/kernel.txt

hackertyper: src/hackertyper.c program_data.o src/hackertyper.h
	$(CC) $(CFLAGS) -o $@ $^
program_data.o:
	cp $(data_file) program_data
	$(LD) -r -b binary program_data -o $@

.PHONY: clean
clean:
	rm -f hackertyper program_data *.o

.PHONY: uninstall
uninstall:
	rm -f $(bindir)/hackertyper
	rm -f $(man1dir)/hackertyper.1
.PHONY: install
install:
	install -m 755 hackertyper $(bindir)
	install -m 644 man/hackertyper.1 $(man1dir)
