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
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "test_utils.h"
#include "../src/globals.h"
#include "../src/validation.h"
#include "../src/process.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

// setup & cleanup
static int setup(void) {
    return 0; // success
}

static int teardown(void) {
    // Do nothing.
    // Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
    return 0; // success
}

static void test_invalid_dates(void) {
    Date dateresult;
    int result_errorcode;
    // act

    //Anzahl Param stimmen nicht
    result_errorcode = validate_and_parse_date(1, 1, 1, 1, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, PARAM_COUNT_ERROR);

    //Anzahl Param stimmen nicht
    result_errorcode = validate_and_parse_date(2, 1, 1, 1, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, PARAM_COUNT_ERROR);

    //Anzahl Param stimmen nicht
    result_errorcode = validate_and_parse_date(5, 1, 1, 1, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, PARAM_COUNT_ERROR);

    //Ungültiger Tag: -01.12.1999
    result_errorcode = validate_and_parse_date(3, -1, 12, 1999, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INVALID_DMY_ERROR);

    //Ungültiger Monat: 12.-12.1999
    result_errorcode = validate_and_parse_date(3, 12, -12, 1999, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INVALID_DMY_ERROR);

    //Ungültiges Jahr: 12.12.-1999
    result_errorcode = validate_and_parse_date(3, 12, 12, -1999, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INVALID_DMY_ERROR);

    //Jahr zu klein: 31.12.1400
    result_errorcode = validate_and_parse_date(3, 31, 12, 1400, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INVALID_GREGORIAN_YEAR_ERROR);

    //Ungültiger Monat: 31.14.1900
    result_errorcode = validate_and_parse_date(3, 31, 14, 1900, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INVALID_MONTH_ERROR);

    //Tag 32 im Monat Januar existiert nicht: 32.01.1900
    result_errorcode = validate_and_parse_date(3, 32, 1, 1900, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INPUT_DATE_INVALID_ERROR);

    //Tag 30 im Februar exisitert nicht: 30.02.1900
    result_errorcode = validate_and_parse_date(3, 30, 2, 1900, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INPUT_DATE_INVALID_ERROR);

    //Tag 31 im April existiert nicht: 31.04.1900
    result_errorcode = validate_and_parse_date(3, 31, 4, 1900, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INPUT_DATE_INVALID_ERROR);

    //29.02.1994 ist kein Schaltjahr: 29.02.1994
    result_errorcode = validate_and_parse_date(3, 29, 2, 1994, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, INPUT_DATE_INVALID_ERROR);

    // assert
}

static void test_valid_dates(void) {
    Date dateresult;
    int result_errorcode;
    // act

    //3 Params sind gültig
    result_errorcode = validate_and_parse_date(3, 1, 1, 1900, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, NO_PARSE_ERROR);

    //4 Params sind gültig
    result_errorcode = validate_and_parse_date(4, 1, 1, 1900, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, NO_PARSE_ERROR);

    //31. Januar ist gültig
    result_errorcode = validate_and_parse_date(3, 31, 01, 2000, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, NO_PARSE_ERROR);

    //30. April ist gültig
    result_errorcode = validate_and_parse_date(3, 30, 04, 2008, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, NO_PARSE_ERROR);

    //28. Februar ist gültig
    result_errorcode = validate_and_parse_date(3, 28, 02, 2000, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, NO_PARSE_ERROR);

    //29. Februar 1996 (Schaltjahr) ist gültig
    result_errorcode = validate_and_parse_date(4, 29, 02, 1996, &dateresult);
    CU_ASSERT_EQUAL(result_errorcode, NO_PARSE_ERROR);

    // assert
}

static void test_addDay_simple(void) {
    Date dateresult = (Date) {12, Jan, 1993};
    // act

    addDay(&dateresult);
    CU_ASSERT_EQUAL(dateresult.day, 13);
    CU_ASSERT_EQUAL(dateresult.month, Jan);
    CU_ASSERT_EQUAL(dateresult.year, 1993);

    // assert
}

static void test_addDay_monthchange(void) {
    Date dateresult = (Date) {31, Jan, 1993};
    // act

    addDay(&dateresult);
    CU_ASSERT_EQUAL(dateresult.day, 01);
    CU_ASSERT_EQUAL(dateresult.month, Feb);
    CU_ASSERT_EQUAL(dateresult.year, 1993);

    // assert
}

static void test_addDay_monthyearchange(void) {
    Date dateresult = (Date) {31, Dec, 1993};
    // act

    addDay(&dateresult);
    CU_ASSERT_EQUAL(dateresult.day, 01);
    CU_ASSERT_EQUAL(dateresult.month, Jan);
    CU_ASSERT_EQUAL(dateresult.year, 1994);

    // assert
}

static void test_addDay_non_leap_year_monthchange(void) {
    Date dateresult = (Date) {28, Feb, 1993};
    // act

    addDay(&dateresult);
    CU_ASSERT_EQUAL(dateresult.day, 01);
    CU_ASSERT_EQUAL(dateresult.month, Mar);
    CU_ASSERT_EQUAL(dateresult.year, 1993);
    // assert
}

static void test_addDay_leap_year_monthchange(void) {
    Date dateresult = (Date) {28, Feb, 1996};
    // act

    addDay(&dateresult);
    CU_ASSERT_EQUAL(dateresult.day, 29);
    CU_ASSERT_EQUAL(dateresult.month, Feb);
    CU_ASSERT_EQUAL(dateresult.year, 1996);
    // assert
}

static void test_addDays_100days_leap_year(void) {
    Date dateresult = (Date) {12, Jan, 1996};
    // act

    addDays(&dateresult, 100);
    CU_ASSERT_EQUAL(dateresult.day, 21);
    CU_ASSERT_EQUAL(dateresult.month, Apr);
    CU_ASSERT_EQUAL(dateresult.year, 1996);
    // assert
}

static void test_addDays_100days(void) {
    Date dateresult = (Date) {12, Jan, 1993};
    // act

    addDays(&dateresult, 100);
    CU_ASSERT_EQUAL(dateresult.day, 22);
    CU_ASSERT_EQUAL(dateresult.month, Apr);
    CU_ASSERT_EQUAL(dateresult.year, 1993);
    // assert
}

static void test_addDays_subtract(void) {
    Date dateresult = (Date) {12, Jan, 1993};
    // act

    addDays(&dateresult, -1);
    CU_ASSERT_EQUAL(dateresult.day, 11);
    CU_ASSERT_EQUAL(dateresult.month, Jan);
    CU_ASSERT_EQUAL(dateresult.year, 1993);
    // assert
}

static void test_addDays_subtract_feb_month_change(void) {
    Date dateresult = (Date) {01, Feb, 1993};
    // act

    addDays(&dateresult, -1);
    CU_ASSERT_EQUAL(dateresult.day, 31);
    CU_ASSERT_EQUAL(dateresult.month, Jan);
    CU_ASSERT_EQUAL(dateresult.year, 1993);
    // assert
}

static void test_addDays_subtract_mar_month_change(void) {
    Date dateresult = (Date) {01, Mar, 1993};
    // act

    addDays(&dateresult, -1);
    CU_ASSERT_EQUAL(dateresult.day, 28);
    CU_ASSERT_EQUAL(dateresult.month, Feb);
    CU_ASSERT_EQUAL(dateresult.year, 1993);
    // assert
}

static void test_addDays_subtract_mar_month_change_leap_year(void) {
    Date dateresult = (Date) {01, Mar, 1996};
    // act

    addDays(&dateresult, -1);

    CU_ASSERT_EQUAL(dateresult.day, 29);
    CU_ASSERT_EQUAL(dateresult.month, Feb);
    CU_ASSERT_EQUAL(dateresult.year, 1996);
    // assert
}

static void test_addDays_subtract_month_year_change(void) {
    Date dateresult = (Date) {01, Jan, 1993};
    // act

    addDays(&dateresult, -1);

    CU_ASSERT_EQUAL(dateresult.day, 31);
    CU_ASSERT_EQUAL(dateresult.month, Dec);
    CU_ASSERT_EQUAL(dateresult.year, 1992);
    // assert
}

static void test_addDays_subtract_100_days(void) {
    Date dateresult = (Date) {12, Jan, 1993};
    // act

    addDays(&dateresult, -100);

    CU_ASSERT_EQUAL(dateresult.day, 4);
    CU_ASSERT_EQUAL(dateresult.month, Oct);
    CU_ASSERT_EQUAL(dateresult.year, 1992);
    // assert
}

/**
 * @brief Registers and runs the tests.
 */
int main(void) {
    // setup, run, teardown
    TestMainBasic("Folgetag", setup, teardown, test_invalid_dates, test_valid_dates, test_addDay_simple,
                  test_addDay_monthchange, test_addDay_monthyearchange, test_addDay_non_leap_year_monthchange,
                  test_addDay_leap_year_monthchange, test_addDays_100days_leap_year, test_addDays_100days,
                  test_addDays_subtract, test_addDays_subtract_feb_month_change, test_addDays_subtract_mar_month_change,
                  test_addDays_subtract_mar_month_change_leap_year, test_addDays_subtract_month_year_change,
                  test_addDays_subtract_100_days
    );
}
