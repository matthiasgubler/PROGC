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
#define INFILE2 "invalid.input"

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

static void test_with_print(void)
{
    // arrange
    const char *out_txt[] = {"Geben Sie die erreichte Punktzahl ein: Geben Sie die erreichte Punktzahl ein: Geben Sie die erreichte Punktzahl ein: Geben Sie die erreichte Punktzahl ein: Wieviele punkte fuer eine 6?: Statistics (3 Students, 15 points needed for mark 6):\n"
                             "Mark 6: 1\n"
                             "Mark 5: 0\n"
                             "Mark 4: 1\n"
                             "Mark 3: 1\n"
                             "Mark 2: 0\n"
                             "Mark 1: 0\n"
                             "\n"
                             "Best mark: \t\t6\n"
                             "Worst mark: \t\t3\n"
                             "Average mark: \t\t4.33\n"
                             "Mark >= 4: \t\t2\n"};
    // act
    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_with_invalid_print(void)
{
    // arrange
    const char *out_txt[] = {"Geben Sie die erreichte Punktzahl ein: Geben Sie die erreichte Punktzahl ein: Sie haben einen ungueltigen Wert eingegeben"};
    // act
    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE2);
    // assert
    CU_ASSERT_EQUAL(exit_code, 1<<8);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

/**
 * @brief Registers and runs the tests.
 */
int main(void)
{
	// setup, run, teardown
	TestMainBasic("Hello World", setup, teardown
				  , testAllInOne, testMarkCalc, test_with_print, test_with_invalid_print
				  );
}
