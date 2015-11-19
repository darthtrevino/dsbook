default: test

binomial.o: target
	gcc -std=c11 -c binomial.c -o target/binomial.o

binomial_test.o: target
	gcc -std=c11 -c binomial_test.c -o target/binomial_test.o

link_tests: binomial_test.o binomial.o
	gcc target/binomial.o target/binomial_test.o -Wall -o target/run_tests

test: link_tests
	./target/run_tests

target:
	mkdir -p target
