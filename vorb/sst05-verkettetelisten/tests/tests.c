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


/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"
#define INFILE_SIMPLE_EXIT "stim-simple-exit.input"
#define INFILE_SIMPLE_ADD_CLEAR "stim-simple-add-clear.input"
#define INFILE_SORTING_TEST "stim-sorting-test.input"
#define INFILE_INSERT_INPUT_VALIDATION "stim-insert-input-validation.input"
#define INFILE_CLEAR_EMPTY "stim-clear-empty.input"
#define INFILE_ADD_REMOVE "stim-add-remove.input"
#define INFILE_FILTER "stim-filter.input"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

// setup & cleanup
static int setup(void) {

    remove_file_if_exists(OUTFILE);
    remove_file_if_exists(ERRFILE);
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

static void test_exit_application(void) {
    // arrange
    const char *out_txt[] = {
            "\nEingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\nUngueltige Eingabe\n"
            "\nEingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_SIMPLE_EXIT);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_simple_add_clear(void) {
    // arrange
    const char *out_txt[] = {
            "\n", "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n",
            "=====Insert=====\n", "Neue Person erfassen\n", "Name: \n", "Vorname: \n", "Alter: \n",
            "Neue Person wird hinzugefuegt\n", "Gubler Matthias, 24\n", "\n",
            "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n", "=====Show=====\n",
            "Gubler Matthias, 24\n", "\n",
            "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n", "=====Insert=====\n",
            "Neue Person erfassen\n", "Name: \n", "Vorname: \n", "Alter: \n", "Neue Person wird hinzugefuegt\n",
            "Colombo Daniele, 29\n", "\n",
            "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n", "=====Show=====\n",
            "Colombo Daniele, 29\n", "Gubler Matthias, 24\n", "\n",
            "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n", "=====Clear=====\n",
            "#### ALLE PERSONEN GELOESCHT ####\n", "\n",
            "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n", "=====Show=====\n",
            "#### LISTE LEER ####\n", "\n",
            "Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n", "=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_SIMPLE_ADD_CLEAR);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_check_sorting(void) {
    // arrange
    const char *out_txt[] = {
            "\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"XXX BBB, 24\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"AAA BBB, 30\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"BBB BBB, 22\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"AAA BBB, 31\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"ZZZ KKK, 21\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"AAA BBB, 30\n"
            ,"AAA BBB, 31\n"
            ,"BBB BBB, 22\n"
            ,"XXX BBB, 24\n"
            ,"ZZZ KKK, 21\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_SORTING_TEST);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_insert_input_validation(void) {
    // arrange
    const char *out_txt[] = {
            "\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"1234567890123456789 1234567890123456789, 30\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"1234567890123456789 1234567890123456789, 30\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
             "Ungueltige Eingabe fuer Alter\n"
            ,"Abbruch\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"1234567890123456789 1234567890123456789, 30\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_INSERT_INPUT_VALIDATION);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_clear_empty(void) {
    // arrange
    const char *out_txt[] = {
            "\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"#### LISTE LEER ####\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Clear=====\n"
            ,"#### ALLE PERSONEN GELOESCHT ####\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"#### LISTE LEER ####\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_CLEAR_EMPTY);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_add_remove(void) {
    // arrange
    const char *out_txt[] = {
            "\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"Gubler Matthias, 24\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"Gubler Matthias, 24\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Remove=====\n"
            ,"Zu loeschende Person angeben\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Person wird geloescht:\n"
            ,"Colombo Daniele, 29\n"
            ,"Person nicht gefunden (NICHTS geloescht)\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"Gubler Matthias, 24\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Remove=====\n"
            ,"Zu loeschende Person angeben\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Person wird geloescht:\n"
            ,"Gubler Matthias, 24\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"#### LISTE LEER ####\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_ADD_REMOVE);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void test_filter(void) {
    // arrange
    const char *out_txt[] = {
            "\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"Gubler Matthias, 25\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"Gugger Monika, 33\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Insert=====\n"
            ,"Neue Person erfassen\n"
            ,"Name: \n"
            ,"Vorname: \n"
            ,"Alter: \n"
            ,"Neue Person wird hinzugefuegt\n"
            ,"Deutsch Thomas, 44\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Show=====\n"
            ,"Deutsch Thomas, 44\n"
            ,"Gubler Matthias, 25\n"
            ,"Gugger Monika, 33\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Filter=====\n"
            ,"Suche nach Personen\n"
            ,"Filter: \n"
            ,"Gubler Matthias, 25\n"
            ,"Gugger Monika, 33\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Filter=====\n"
            ,"Suche nach Personen\n"
            ,"Filter: \n"
            ,"Gubler Matthias, 25\n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Filter=====\n"
            ,"Suche nach Personen\n"
            ,"Filter: \n"
            ,"\n"
            ,"Eingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), F(ilter), C(lear), E(nd)\n"
            ,"=====Good Bye=====\n"
    };
    // act
    int
    exit_code = system(XSTR(TARGET)
    " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_FILTER);
    // assert
    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

/**
 * @brief Registers and runs the tests.
 */
int main(void) {
    // setup, run, teardown
    TestMainBasic("Verketteteliste", setup, teardown, test_person_compareTo, test_person_areEquals,
                  test_list_addPerson_removePerson_one, test_list_addPerson_removePerson_multiple,
                  test_list_clearList_empty, test_list_clearList, test_exit_application, test_simple_add_clear,
                  test_check_sorting, test_insert_input_validation, test_clear_empty, test_add_remove, test_filter

    );
}
