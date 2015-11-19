#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "binomial.h"

const double ABOUT_EQUAL_SIGMA = 0.000001;

void assert_about_equals(double actual, double expected, char *name) {
  double diff = fabs(actual - expected);
  assert(diff < ABOUT_EQUAL_SIGMA && name);
}

/**
 *  Binomial with Roots=-2,2
 *  y = (x - 2)(x + 2)
 *  y = x^2 - 4
 */
void test_simple_binomial() {
  BinomialRoots roots;
  int retcode = computeBinomial(1, 0, -4, &roots);
  assert(retcode == 0 && "test_simple_binomial() return code");
  assert_about_equals(roots.root1, 2.0, "test_simple_binomial() root 1");
  assert_about_equals(roots.root2, -2.0, "test_simple_binomial() root 2");
}

void test_non_quadratic() {
  BinomialRoots roots;
  int retcode = computeBinomial(0, 1, -4, &roots);
  assert(retcode == 1 && "test_non_quadratic() return code");
}

void test_imaginary_roots() {
  BinomialRoots roots;
  int retcode = computeBinomial(1, 0, 4, &roots);
  assert(retcode == 2 && "test_imaginary_roots() return code");
}

int main() {
  test_simple_binomial();
  test_non_quadratic();
  test_imaginary_roots();
}
