//
// Created by Matthias Gubler on 15.09.18.
//

#ifndef PROGC_LIST_H
#define PROGC_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "person.h"

#define SUCCESS 0
#define MEMORY_ERROR -1

typedef struct LE ListElement;
typedef ListElement *ListElementPtr;
struct LE {
    Person *person; // In diesem Listenelement gespeicherte Person.
    ListElement *next; // Pointer auf das nächstfolgende Element in der Liste.
    ListElement *previous; // Pointer auf das vorherige Element
};

int initList();

int addPerson(Person *person);

void removePerson(Person *person);

void removeListElement(ListElementPtr listElementToRemove);

ListElementPtr getListElementByPerson(Person *person);

void printCurrentList();

void clearList();

#endif //PROGC_LIST_H
