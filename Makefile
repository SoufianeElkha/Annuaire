TARGET=directory
CC=gcc
FLAGS=-g -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer
LIBS=-lm
OBJECTS=directory.o hash.o commandes.o
HEADERS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(FLAGS) $(LIBS) -o $@

$(OBJECTS): %.o: %.c $(HEADERS)
	$(CC) -c $(FLAGS) $<

clean:
	rm -rf *.o $(TARGET)

.PHONY: clean all
