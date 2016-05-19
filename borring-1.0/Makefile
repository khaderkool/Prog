
DESTDIR ?=
PREFIX ?= /usr/local

all:
	gcc borring.c -o borring

clean:
	rm -rf borring

install: borring
	install -m 0755 -d $(DESTDIR)$(PREFIX)/bin
	install -m 0755 borring $(DESTDIR)$(PREFIX)/bin


