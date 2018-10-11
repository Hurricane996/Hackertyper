SHELL = /bin/sh

prefix=/usr/local
mandir=/usr/local/share/man

data-file = data/kernel.txt

hackertyper: src/main.c src/data.h
	$(CC) $(CFLAGS) $? -o $@ 
src/data.h: data.txt
	xxd -i $? > $@
data.txt: $(data-file)
	cp $? $@
clean:
	rm -f hackertyper src/data.h data.txt
install: hackertyper
	install -m 755 hackertyper $(prefix)/bin
	install -m 644 doc/hackertyper.1 $(mandir)/man1

