CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

SRCDIR = code/src/
OBJDIR = code/objects/

SOURCES = $(shell find $(SRCDIR) -name "*.c")
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

EXEC = game

.PHONY : clean all

all : $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o : 
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJECTS) $(EXEC)

p-% : ; @echo $* = $($*)
