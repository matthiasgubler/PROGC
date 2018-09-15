//
// Created by Matthias Gubler on 15.09.18.
//

#ifndef PROGC_MENU_H
#define PROGC_MENU_H

#include "person.h"

#define IO_ERROR 1
#define BUFFER_ERROR 3

typedef enum {
    Insert = 'I', Remove = 'R', Show = 'S', Clear = 'C', End = 'E', Invalid = '0'
} Menu;

Menu showMenuAndGetSelectedFunction();
int createPersonWizard(const char * wizardText, Person * person);

#endif //PROGC_MENU_H
