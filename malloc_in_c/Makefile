CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
CC=gcc

output:
	$(CC) $(CFLAGS) -o test test.c
	./test

heap: main.c heap.c heap.h
	$(CC) $(CFLAGS) -o main main.c heap.c 
	./main

test_run:
	./test
