CC = gcc
CFLAGS = -lm -Wall -Werror

.PHONY: all clean

default: all

all: main

main: Main.c TP3.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f main
