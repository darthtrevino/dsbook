/**
 * A structure that contains Binomial Roots
 */
typedef struct {
    double root1;
    double root2;
} BinomialRoots;

/**
 * A function that computes the binomial roots of a quadratic function in the form
 * y = ax^2 + bx + c.
 *
 * Result Codes:
 *  0 - success
 *  1 - result is undefined due to divide-by-zero
 *  2 - result is imaginary
 */
int computeBinomial(double a, double b, double c, BinomialRoots *pResult);
