CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wstrict-prototypes -pedantic
#LIBS = -lm
EXEC = histogram
#OBJS = histogram.o

#grabs the files that have type .c
SOURCES = $(wildcard *.c)
#replaces all file names to be of type .o
OBJECTS = $(subst .c,.o,$(SOURCES))

.PHONY: all clean

all: $(EXEC)

histogram : histogram.o
	$(CC) -o $@ $^ 

%.o : %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJECTS) $(EXEC)  
