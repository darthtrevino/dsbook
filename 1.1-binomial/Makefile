CC = gcc
CFLAGS = -std=c11
LFLAGS = -Wall -lm

default: test

target/binomial.o: binomial.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/binomial_test.o: binomial_test.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/test: target/binomial_test.o target/binomial.o
	$(CC) $^ $(LFLAGS) -o $@

test: target/test
	./target/$@

target:
	mkdir -p $@

clean:
	rm target/*

.PHONY: clean
