/**
 * A Test Method is Function Pointer to a Simple Function
 */
typedef void (test_method)();

/**
 * Prepares to Run the Test Suite
 */
void tests_begin(const char *suite);

/**
 * Runs the given test method
 */
void run_test(test_method fn);

/**
 * Indicate that tests are complete after the tests are run
 */
void tests_complete();
