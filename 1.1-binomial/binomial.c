#include "binomial.h"
#include <math.h>

const double SIGMA = 0.0000001;

double sqrtOperand(double a, double b, double c) {
  double bsquare = pow(b, 2.0);
  return bsquare - 4.0 * a * c;
}

/**
 * Implementation of computeBinomial
 */
int computeBinomial(double a, double b, double c, BinomialRoots *pResult) {
  // Prevent divide-by-zero, which occurs when the input is not a quadratic.
  if (fabs(a) < SIGMA) {
    return 1;
  }
  // Check if the roots are imaginary
  double rootTarget = sqrtOperand(a, b, c);
  if (rootTarget < 0) {
    return 2;
  }
  
  double denominator = a * 2.0;
  double negB = b * -1.0;
  double additiveTerm = sqrt(rootTarget);
  pResult->root1 = (negB + additiveTerm) / denominator;
  pResult->root2 = (negB - additiveTerm) / denominator;
  return 0;
}
