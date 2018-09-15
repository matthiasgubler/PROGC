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
#include <string.h>
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

static void test_person_compareTo(void) {
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

static void test_person_areEquals(void) {
    Person person1;
    Person person2;
    person1 = (Person) {"Gubler", "Matthias", 25};
    person2 = (Person) {"Gubler", "Matthias", 25};
    CU_ASSERT_TRUE(areEquals(&person1, &person2));

    person2 = (Person) {"Gubler", "Matthias", 26};
    CU_ASSERT_FALSE(areEquals(&person1, &person2));

    person2 = (Person) {"Gubler", "Matthiass", 25};
    CU_ASSERT_FALSE(areEquals(&person1, &person2));

    person2 = (Person) {"Gublerr", "Matthias", 25};
    CU_ASSERT_FALSE(areEquals(&person1, &person2));

    person2 = (Person) {"Colombo", "Daniele", 33};
    CU_ASSERT_FALSE(areEquals(&person1, &person2));
}

static void test_list_addPerson_removePerson_one(void) {
    Person *person = initializePerson();
    strcpy(person->name, "Gubler");
    strcpy(person->firstname, "Matthias");
    person->age = 25;

    initList();

    addPerson(person);
    ListElementPtr resultPersonAfterAdd = getListElementByPerson(person);
    CU_ASSERT_NOT_EQUAL(resultPersonAfterAdd->person, NULL);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd->person->firstname, "Matthias"), 0);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd->person->name, "Gubler"), 0);
    CU_ASSERT_EQUAL(resultPersonAfterAdd->person->age, 25);

    removePerson(person);
    ListElementPtr resultPersonAfterRemove = getListElementByPerson(person);
    CU_ASSERT_EQUAL(resultPersonAfterRemove, NULL);
}

static void test_list_addPerson_removePerson_multiple(void) {
    Person *person1 = initializePerson();
    strcpy(person1->name, "Gubler");
    strcpy(person1->firstname, "Matthias");
    person1->age = 25;

    Person *person2 = initializePerson();
    strcpy(person2->name, "Colombo");
    strcpy(person2->firstname, "Daniele");
    person2->age = 33;

    initList();
    addPerson(person1);
    addPerson(person2);

    ListElementPtr resultPersonAfterAdd = getListElementByPerson(person1);
    CU_ASSERT_NOT_EQUAL(resultPersonAfterAdd->person, NULL);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd->person->firstname, "Matthias"), 0);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd->person->name, "Gubler"), 0);
    CU_ASSERT_EQUAL(resultPersonAfterAdd->person->age, 25);

    ListElementPtr resultPersonAfterAdd2 = getListElementByPerson(person2);
    CU_ASSERT_NOT_EQUAL(resultPersonAfterAdd2->person, NULL);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd2->person->firstname, "Daniele"), 0);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd2->person->name, "Colombo"), 0);
    CU_ASSERT_EQUAL(resultPersonAfterAdd2->person->age, 33);

    removePerson(person1);
    ListElementPtr resultPersonAfterRemove = getListElementByPerson(person1);
    CU_ASSERT_EQUAL(resultPersonAfterRemove, NULL);

    resultPersonAfterAdd2 = getListElementByPerson(person2);
    CU_ASSERT_NOT_EQUAL(resultPersonAfterAdd2->person, NULL);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd2->person->firstname, "Daniele"), 0);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd2->person->name, "Colombo"), 0);
    CU_ASSERT_EQUAL(resultPersonAfterAdd2->person->age, 33);

    removePerson(person2);
    ListElementPtr resultPersonAfterRemove2 = getListElementByPerson(person2);
    CU_ASSERT_EQUAL(resultPersonAfterRemove2, NULL);
}

static void test_list_clearList_empty(void) {
    initList();
    clearList();
}

static void test_list_clearList(void) {

    Person *person1 = initializePerson();
    strcpy(person1->name, "Gubler");
    strcpy(person1->firstname, "Matthias");
    person1->age = 25;

    Person *person2 = initializePerson();
    strcpy(person2->name, "Colombo");
    strcpy(person2->firstname, "Daniele");
    person2->age = 33;

    initList();
    addPerson(person1);
    addPerson(person2);

    ListElementPtr resultPersonAfterAdd = getListElementByPerson(person1);
    CU_ASSERT_NOT_EQUAL(resultPersonAfterAdd->person, NULL);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd->person->firstname, "Matthias"), 0);
    CU_ASSERT_EQUAL(strcmp(resultPersonAfterAdd->person->name, "Gubler"), 0);
    CU_ASSERT_EQUAL(resultPersonAfterAdd->person->age, 25);

    clearList();

    ListElementPtr resultPersonAfterRemove = getListElementByPerson(person1);
    CU_ASSERT_EQUAL(resultPersonAfterRemove, NULL);
    ListElementPtr resultPersonAfterRemove2 = getListElementByPerson(person2);
    CU_ASSERT_EQUAL(resultPersonAfterRemove2, NULL);
}

/**
 * @brief Registers and runs the tests.
 */
int main(void) {
    // setup, run, teardown
    TestMainBasic("Verketteteliste", setup, teardown, test_person_compareTo, test_person_areEquals,
                  test_list_addPerson_removePerson_one, test_list_addPerson_removePerson_multiple,
                  test_list_clearList_empty, test_list_clearList

    );
}
