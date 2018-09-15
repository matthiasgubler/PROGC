//
// Created by Matthias Gubler on 15.09.18.
//

#include "list.h"

ListElementPtr anchorListElementPtr;
ListElementPtr currentElementPtr;

int initList() {
    //Allocate Anchor Element
    anchorListElementPtr = (ListElementPtr) malloc(sizeof(ListElement));
    if (anchorListElementPtr == NULL) {
        return MEMORY_ERROR;
    }

    anchorListElementPtr->next = anchorListElementPtr;
    anchorListElementPtr->previous = anchorListElementPtr;
    currentElementPtr = anchorListElementPtr;

    return SUCCESS;
}

int addPerson(Person *person) {
    //Allocate new ListElement and Check for success
    ListElementPtr newElementPtr = (ListElementPtr) malloc(sizeof(ListElement));
    if (newElementPtr == NULL) {
        return MEMORY_ERROR;
    }

    //Set new Person Data
    newElementPtr->person = person;

    //New person ist always the last element -> Set the next Ptr to the Anchor Element
    newElementPtr->next = anchorListElementPtr;
    anchorListElementPtr->previous = newElementPtr;

    //Set the Pointer of the last element to the new element and vice versa -> overwrite the "currentElement"
    currentElementPtr->next = newElementPtr;
    newElementPtr->previous = currentElementPtr;
    currentElementPtr = newElementPtr;

    return SUCCESS;
}

void removePerson(Person *person) {
    ListElementPtr listElementToDelete = getListElementByPerson(person);
    if(listElementToDelete != NULL){
        removeListElement(listElementToDelete);
    }else{
        (void)printf("Person nicht gefunden (NICHTS gelöscht)\n");
    }
}

void removeListElement(ListElementPtr listElementToRemove) {
    ListElementPtr previousListElement = listElementToRemove->previous;
    ListElementPtr nextListElement = listElementToRemove->next;

    //Forget the element to be removed in the chain
    previousListElement->next = nextListElement;
    nextListElement->previous = previousListElement;
    free(listElementToRemove);
    free(listElementToRemove->person);

    currentElementPtr = previousListElement;
}

void clearList() {
    ListElementPtr currentSearchPtr = anchorListElementPtr->next;
    while (currentSearchPtr != anchorListElementPtr) {
        removeListElement(currentSearchPtr);
        currentSearchPtr = currentSearchPtr->next;
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
    ListElementPtr currentSearchPtr = anchorListElementPtr->next;
    while (currentSearchPtr != anchorListElementPtr) {
        prettyPrintPerson(currentSearchPtr->person);
        currentSearchPtr = currentSearchPtr->next;
    }
}
