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
#include "../src/list.h"
#include "../src/person.h"
#include "../src/menu.h"

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

static void test_Person_compareTo(void) {
    int compareResult;
    Person person1;
    Person person2;

    person2 = (Person) {"Gubler", "Matthias", 25};
    compareResult = compareTo(NULL, &person2);
    CU_ASSERT_TRUE(compareResult < 0);

    person1 = (Person) {"Gubler", "Matthias", 25};
    compareResult = compareTo(&person1, NULL);
    CU_ASSERT_TRUE(compareResult > 0);

    person1 = (Person) {"Colombo", "Daniele", 29};
    person2 = (Person) {"Gubler", "Matthias", 25};
    compareResult = compareTo(&person1, &person2);
    printf("FREDYFREDYFREDYFREDY %d\n", compareResult);
    CU_ASSERT_TRUE(compareResult < 0);

    person1 = (Person) {"Gubler", "Matthias", 25};
    person2 = (Person) {"Colombo", "Daniele", 29};
    compareResult = compareTo(&person1, &person2);
    CU_ASSERT_TRUE(compareResult > 0);

    person1 = (Person) {"Gubler", "Matthias", 25};
    person2 = (Person) {"Gubler", "Matthias", 25};
    compareResult = compareTo(&person1, &person2);
    CU_ASSERT_EQUAL(compareResult, 0);

    person1 = (Person) {"Gubler", "Matthias", 24};
    person2 = (Person) {"Gubler", "Matthias", 25};
    compareResult = compareTo(&person1, &person2);
    CU_ASSERT_TRUE(compareResult < 0);

    person1 = (Person) {"Gubler", "Matthias", 25};
    person2 = (Person) {"Gubler", "Matthias", 24};
    compareResult = compareTo(&person1, &person2);
    CU_ASSERT_TRUE(compareResult > 0);

    person1 = (Person) {"Gubler", "Martin", 25};
    person2 = (Person) {"Gubler", "Matthias", 25};
    compareResult = compareTo(&person1, &person2);
    CU_ASSERT_TRUE(compareResult < 0);

    person1 = (Person) {"Gubler", "Matthias", 25};
    person2 = (Person) {"Gubler", "Martin", 25};
    compareResult = compareTo(&person1, &person2);
    CU_ASSERT_TRUE(compareResult > 0);
}


/**
 * @brief Registers and runs the tests.
 */
int main(void) {
    // setup, run, teardown
    TestMainBasic("Verketteteliste", setup, teardown, test_Person_compareTo

    );
}
