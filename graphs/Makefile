# change application name here (executable output name)
TARGET=example

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

CAIROLIB=`pkg-config --cflags --libs cairo`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(CAIROLIB)

OBJS=example.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

example.o: example.c
	$(CC) -c $(CCFLAGS) example.c $(CAIROLIB) -o example.o

clean:
	rm -f *.o $(TARGET)
	rm -f *.png $(TARGET)
	rm -f *.h.gch $(TARGET)
