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
#include "../src/pointer.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"

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

static void test_word_exists(void) {
    char *wordList[100] = {"Z", "A", "F", "G", "M"};
    CU_ASSERT_EQUAL(wordExists(wordList, "A"), 1);
    CU_ASSERT_EQUAL(wordExists(wordList, "N"), 0);
}

static void test_swap(void) {
    char * words[5] = {"A", "B", "C", "D", "E"};
    swapIt(&words[1], &words[3]);
    CU_ASSERT_EQUAL(words[1], "D");
    CU_ASSERT_EQUAL(words[3], "B");
}

static void test_sort_desc(void)
{
    char *wordList[100] = {"Z", "A", "F", "G", "M"};
    sort(wordList, 5, 1);
    CU_ASSERT_EQUAL(wordList[4], "A");
    CU_ASSERT_EQUAL(wordList[3], "F");
    CU_ASSERT_EQUAL(wordList[2], "G");
    CU_ASSERT_EQUAL(wordList[1], "M");
    CU_ASSERT_EQUAL(wordList[0], "Z");
}

// tests
static void test_sort(void)
{
    char *wordList[100] = {"Z", "A", "F", "G", "M"};
    sort(wordList, 5, 0);
    CU_ASSERT_EQUAL(wordList[0], "A");
    CU_ASSERT_EQUAL(wordList[1], "F");
    CU_ASSERT_EQUAL(wordList[2], "G");
    CU_ASSERT_EQUAL(wordList[3], "M");
    CU_ASSERT_EQUAL(wordList[4], "Z");
}

/**
 * @brief Registers and runs the tests.
 */
int main(void)
{
	// setup, run, teardown
	TestMainBasic("Hello World", setup, teardown
				  , test_sort, test_sort_desc, test_word_exists, test_swap
				  );
}
