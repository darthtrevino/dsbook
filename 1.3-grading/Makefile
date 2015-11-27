CC = gcc
CFLAGS = -std=c99
LFLAGS = -Wall

default: build test
test: grading_test appsupport_test
build: target/grading

watch:
	while true; do \
		make test; \
		inotifywait -qre close_write .; \
	done

target/grading.o: grading.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/appsupport.o: appsupport.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/testsupport.o: testsupport.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/main.o: main.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/grading_test.o: grading_test.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/appsupport_test.o: appsupport_test.c target
	$(CC) $(CFLAGS) -c $< -o $@

target/grading: target/grading.o target/appsupport.o target/main.o
	$(CC) $(LFLAGS) $^ -o $@

target/grading_test: target/grading.o target/grading_test.o target/testsupport.o
	$(CC) $(LFLAGS) $^ -o $@

target/appsupport_test: target/appsupport.o target/appsupport_test.o target/testsupport.o
	$(CC) $(LFLAGS) $^ -o $@

grading_test: target/grading_test
	./$<

appsupport_test: target/appsupport_test
	./$<

target:
	mkdir -p $@

clean:
	rm target/*

.PHONY: clean build test grading_test appsupport_test watch
