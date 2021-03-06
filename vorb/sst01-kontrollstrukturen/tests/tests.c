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
#include "../src/sst01.h"

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

// tests
static void test_main_with_zero_args(void)
{
	// arrange
	const char *out_txt[] = { "Keine Argumente" };
	const char *err_txt[] = { };
	// act
	int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE);
	// assert
	CU_ASSERT_EQUAL(exit_code, (1 << 8));
	assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
	assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

static void test_assignment(void)
{
    struct Assignment1Result result = createAssignment1Result(13);
    CU_ASSERT_EQUAL(result.value, 13);
    CU_ASSERT_EQUAL(result.signedValue, 13);
    CU_ASSERT_EQUAL(result.addValue, 12);
    CU_ASSERT_EQUAL(result.einer, -14);
    CU_ASSERT_EQUAL(result.zweier, -13);

}

static void test_main_with_two_invalid_args(void)
{
	// arrange
	const char *out_txt[] = { "Argument1: invalid value" };
	const char *err_txt[] = { };
	// act
	int exit_code = system(XSTR(TARGET) " A B 1>" OUTFILE " 2>" ERRFILE);
	// assert
	CU_ASSERT_EQUAL(exit_code, (1 << 8));
	assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
	assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

static void test_main_with_two_invalid_args_2(void)
{
    // arrange
    const char *out_txt[] = { "Argument2: invalid value" };
    const char *err_txt[] = { };
    // act
    int exit_code = system(XSTR(TARGET) " 130 19 1>" OUTFILE " 2>" ERRFILE);
    // assert
    CU_ASSERT_EQUAL(exit_code, (1 << 8));
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

/**
 * @brief Registers and runs the tests.
 */
int main(void)
{
	// setup, run, teardown
	TestMainBasic("Hello World", setup, teardown
				  , test_main_with_zero_args
				  , test_assignment
				  , test_main_with_two_invalid_args
				  , test_main_with_two_invalid_args_2
				  );
}
