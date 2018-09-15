//
// Created by Matthias Gubler on 15.09.18.
//

#ifndef PROGC_PERSON_H
#define PROGC_PERSON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    char firstname[20];
    unsigned age;
} Person;

bool areEquals(Person *person1, Person *person2);

void prettyPrintPerson(Person *person);

Person * initializePerson();

void freePerson(Person *person);

#endif //PROGC_PERSON_H
