#include "testsupport.h";
#include <stdio.h>

void tests_begin(const char *suite) {
  printf("\ntesting %s: ", suite);
}

void run_test(test_method fn) {
  fn();
  printf(".");
}

void tests_complete() {
  printf("done!\n\n");
}
