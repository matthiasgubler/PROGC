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
static void testMarkCalc(void)
{
    int note5 = calcNote(20, 28);
    int note1 = calcNote(0, 28);
    int note6 = calcNote(20, 20);
    int note66 = calcNote(200, 20);

    CU_ASSERT_EQUAL(note5, 5);
    CU_ASSERT_EQUAL(note1, 1);
    CU_ASSERT_EQUAL(note6, 6);
    CU_ASSERT_EQUAL(note66, 6);
}

// tests

static void testAllInOne(void)
{
    int punkte[100] = {0}, noten[100] = {0};
    for (int x=0; x<100; x++) {
        punkte[x] = -1;
    }
    int minimum6 = 15;
    struct MarkCounter counter = {0, 0, 0, 0, 0, 0};

    punkte[0] = 20;
	punkte[1] = 10;
	punkte[2] = 5;

    (void)calculateStatistics(punkte, noten, minimum6, &counter);

    int worst = findWorstMark(&counter);
    int best = findBestMark(&counter);
    int morethan4 = calcMoreThan4(&counter);
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
				  , testAllInOne, testMarkCalc
				  );
}
