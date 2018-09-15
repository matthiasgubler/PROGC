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
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "test_utils.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"
#define INFILE "test-input.input"
#define INFILE2 "test-input2.input"

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

static void test_main_with_basic_input(void)
{
    const char *out_txt[] = {"Woerter: 2\n"
                            "Zeichen: 9\n"};
	int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    CU_ASSERT_EQUAL(exit_code, 0);
}

static void test_main_with_no_words(void)
{
    const char *out_txt[] = {"Woerter: 0\n"
                             "Zeichen: 0\n"};
    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE2);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    CU_ASSERT_EQUAL(exit_code, 0);
}

/**
 * @brief Registers and runs the tests.
 */
int main(void)
{
	// setup, run, teardown
	TestMainBasic("Hello World", setup, teardown
				  , test_main_with_basic_input
				  , test_main_with_no_words
				  );
}
