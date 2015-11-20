CC = gcc
CFLAGS = -std=c11
LFLAGS = -Wall

default: test

target/grading.o: grading.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/grading_test.o: grading_test.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/test: target/grading.o target/grading_test.o
	$(CC) $(LGLAGS) $^ -Wall -o $@

test: target/test
	./$<

target:
	mkdir -p $@

clean:
	rm target/*

.PHONY: clean
