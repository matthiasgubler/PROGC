/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Test suite for the given package.
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "test_utils.h"
#include "../src/stats.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"
#define INFILE "valid.input"

// setup & cleanup
static int setup(void)
{
	remove_file_if_exists(OUTFILE);
	remove_file_if_exists(ERRFILE);
	return 0; // success
}

static int teardown(void)
{
	// Do nothing.
	// Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
	return 0; // success
}

// tests
static void test_main_with_zero_args(void)
{
	//const char *out_txt[] = {"HANS"};
	//int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE);
	//assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    int punkte[100] = {0}, noten[100] = {0};
    int minimum6 = 15;
    struct MarkCounter counter = {0, 0, 0, 0, 0, 0};

    punkte[0] = 20;
	punkte[1] = 10;
	punkte[2] = 5;

    (void)calculateStatistics(punkte, noten, minimum6, &counter);

    int worst = findWorstMark(&counter);
    int best = findBestMark(&counter);
    int morethan4 = calcMoreThan4(&counter);
    printf("hehe %d", best);
    CU_ASSERT_EQUAL(worst, 3);
    CU_ASSERT_EQUAL(best, 6);
    CU_ASSERT_EQUAL(morethan4, 2);

    CU_ASSERT_EQUAL(counter.einer, 0);
    CU_ASSERT_EQUAL(counter.zweier, 0);
    CU_ASSERT_EQUAL(counter.dreier, 1);
    CU_ASSERT_EQUAL(counter.vierer, 1);
    CU_ASSERT_EQUAL(counter.fuenfer, 0);
    CU_ASSERT_EQUAL(counter.sechser, 1);










}

/**
 * @brief Registers and runs the tests.
 */
int main(void)
{
	// setup, run, teardown
	TestMainBasic("Hello World", setup, teardown
				  , test_main_with_zero_args
				  );
}
