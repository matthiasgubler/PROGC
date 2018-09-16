//
// Created by Matthias Gubler on 15.09.18.
//

#include "list.h"

ListElementPtr searchInsertIndex(Person *person);

ListElementPtr anchorListElementPtr;

int initList() {
    //Allocate Anchor Element
    anchorListElementPtr = (ListElementPtr) malloc(sizeof(ListElement));
    if (anchorListElementPtr == NULL) {
        return MEMORY_ERROR;
    }

    anchorListElementPtr->next = anchorListElementPtr;
    anchorListElementPtr->previous = anchorListElementPtr;

    return SUCCESS;
}

int addPerson(Person *person) {
    ListElementPtr insertBeforePtr = searchInsertIndex(person);
    //Allocate new ListElement and Check for success
    ListElementPtr newElementPtr = (ListElementPtr) malloc(sizeof(ListElement));
    if (newElementPtr == NULL) {
        return MEMORY_ERROR;
    }

    //Set new Person Data
    newElementPtr->person = person;

    //Set the next and previous pointer for the new element
    newElementPtr->next = insertBeforePtr;
    newElementPtr->previous = insertBeforePtr->previous;
    //Set the next pointer of the previous one to the new element
    insertBeforePtr->previous->next = newElementPtr;

    //Set the previous pointer of the followup person to the new element
    insertBeforePtr->previous = newElementPtr;

    return SUCCESS;
}

ListElementPtr searchInsertIndex(Person *person) {
    ListElementPtr resultListElementPtr = anchorListElementPtr->next;

    while (compareTo(person, resultListElementPtr->person) > 0 && resultListElementPtr != anchorListElementPtr) {
        resultListElementPtr = resultListElementPtr->next;
    }
    return resultListElementPtr;
}

void removePerson(Person *person) {
    ListElementPtr listElementToDelete = getListElementByPerson(person);
    if (listElementToDelete != NULL) {
        removeListElement(listElementToDelete);
    } else {
        (void) printf("Person nicht gefunden (NICHTS geloescht)\n");
    }
}

void removeListElement(ListElementPtr listElementToRemove) {
    ListElementPtr previousListElement = listElementToRemove->previous;
    ListElementPtr nextListElement = listElementToRemove->next;

    //Forget the element to be removed in the chain
    previousListElement->next = nextListElement;
    nextListElement->previous = previousListElement;
    free(listElementToRemove->person);
    free(listElementToRemove);
}

void clearList() {
    ListElementPtr currentSearchPtr = anchorListElementPtr->next;
    while (anchorListElementPtr != anchorListElementPtr->next) {
        if (currentSearchPtr != anchorListElementPtr) {
            removeListElement(currentSearchPtr);
            currentSearchPtr = currentSearchPtr->next;
        }
    }
}

ListElementPtr getListElementByPerson(Person *person) {
    bool found = false;
    ListElementPtr currentSearchPtr = anchorListElementPtr->next;
    while (found == false && currentSearchPtr != anchorListElementPtr) {
        if (areEquals(currentSearchPtr->person, person)) {
            return currentSearchPtr;
        }
        currentSearchPtr = currentSearchPtr->next;
    }
    return NULL;
}

void printCurrentList() {
    if (anchorListElementPtr == anchorListElementPtr->next) {
        (void) printf("#### LISTE LEER ####\n");
    }

    ListElementPtr currentSearchPtr = anchorListElementPtr->next;
    while (currentSearchPtr != anchorListElementPtr) {
        prettyPrintPerson(currentSearchPtr->person);
        currentSearchPtr = currentSearchPtr->next;
    }
}
