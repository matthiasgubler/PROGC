//
// Created by Matthias Gubler on 15.09.18.
//

#include "person.h"
#include <string.h>

bool areEquals(Person *person1, Person *person2) {
    if (person1 != NULL && person2 != NULL) {
        if (person1->age == person2->age
            && strcmp(person1->firstname, person2->firstname) == 0
            && strcmp(person1->name, person2->name) == 0) {
            return true;
        }
    }
    return false;
}

void prettyPrintPerson(Person *person) {
    (void) printf("%s %s, %d\n", person->name, person->firstname, person->age);
}

Person * initializePerson(){
    return (Person*)malloc(sizeof(Person));
}

void freePerson(Person *person){
    free(person);
}
