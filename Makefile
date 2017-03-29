TARGET=app

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) $(patsubst %.c, %.o, $(wildcard */*.c))
HEADERS = $(wildcard *.h) $(wildcard */*.h)

.PHONY: default all clean

%.o: %.c $(HEADERS)
	gcc	-c	$<	-o	$@	$(LDFLAGS)	$(GTKLIB)

program: $(OBJECTS)
	gcc	$(OBJECTS)	-o	$(TARGET)	$(LDFLAGS)
	-rm -f */*.o *.o *.h.gch */*.h.gch
	-rm -r dist
	-mkdir dist
	-cp app dist/
	-cp css.css dist/
	-cp -r glade dist/
