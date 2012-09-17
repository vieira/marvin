# $Id: Marvin, The Bot v0.1 2009/01/31 02:25:00 vieira@yubo.be $
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
CFLAGS =-c -pedantic -Wall

all: marvin

marvin : $(OBJECTS)
	cc $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -fr $(OBJECTS) marvin
