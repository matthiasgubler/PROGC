//
// Created by Matthias Gubler on 15.09.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "menu.h"
#include "person.h"
#include "list.h"

#define CONSOLE_BUFFER_SIZE 256

char caInternalBuffer[CONSOLE_BUFFER_SIZE];

int readInput(const char *format, ...);

Menu showMenuAndGetSelectedFunction() {
    char menuSelectionChar;
    Menu menuSelection;

    (void) printf("\nEingabe der gewuenschten Funktion: I(nsert), R(emove), S(how), C(lear), E(nd)\n");

    int scannedParams = readInput("%c", &menuSelectionChar);
    if (scannedParams == 1) {
        menuSelection = (Menu) menuSelectionChar;
        return menuSelection;
    } else {
        return Invalid;
    }
}

int createPersonWizard(const char * wizardText, Person * person) {
    char name[20];
    char firstname[20];
    int age;

    (void) printf("%s", wizardText);
    (void) printf("Name: ");
    if (readInput("%19s", &name) != 1) {
        (void)printf("Ungültige Eingabe für Name\n");
        return -1;
    }

    (void) printf("\nVorname: ");
    if (readInput("%19s", &firstname) != 1) {
        (void)printf("Ungültige Eingabe für Vorname\n");
        return -1;
    }

    (void) printf("\nAlter: ");
    if (readInput("%d", &age) != 1) {
        (void)printf("Ungültige Eingabe für Alter\n");
        return -1;
    }

    (void) printf("\n");
    (void)strcpy(person->name, name);
    (void)strcpy(person->firstname, firstname);
    person->age = age;
    return 0;
}

int readInput(const char *format, ...) {
    int count;
    va_list arg;
    va_start(arg, format);

    if (fgets(caInternalBuffer, CONSOLE_BUFFER_SIZE, stdin) == NULL) {
        exit(IO_ERROR);
    }
    count = vsscanf(caInternalBuffer, format, arg);
    va_end(arg);

    if (count == EOF) {
        exit(BUFFER_ERROR);
    }
    return count;
}

