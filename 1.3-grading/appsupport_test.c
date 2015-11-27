#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "appsupport.h"
#include "testsupport.h"

void test_is_command_1();

int main() {
  tests_begin("appsupport");
  run_test(test_is_command_1);
  tests_complete();
  return 0;
}

void test_is_command_1() {
  assert(false == isCommand("quit\n", "quit") && "test_is_command_1()");
}
