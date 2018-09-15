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
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "list.h"
#include "person.h"

#define EXIT_OK 0
#define EXIT_ERROR 1

bool run = true;

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments
 *                  with argv[0] being the command call
 *                  argv[1] the 1st argument, ...
 *                  argv[argc-1] the last argument.
 * @returns Returns EXIT_SUCCESS (=0) on success,
 *                  EXIT_FAILURE (=1) if more than one argument is given.
 */
int main(int argc, char *argv[]) {
    if(initList() != SUCCESS){
        exit(EXIT_ERROR);
    }

    do {
        switch (showMenuAndGetSelectedFunction())
        {
            case Insert:
                (void) printf("=====Insert=====\n");
                Person * person;
                if((person = initializePerson(person)) == NULL){
                    (void) printf("Could not allocate Memory for Person");
                    exit(EXIT_ERROR);
                }
                if(createPersonWizard("Neue Person erfassen\n", person) == 0){
                    (void)printf("Neue Person wird hinzugefügt\n");
                    prettyPrintPerson(person);
                    addPerson(person);
                }else{
                    (void)printf("Abbruch\n");
                    freePerson(person);
                }
            break;
            case Remove:
                (void) printf("=====Remove=====\n");
                Person personToDelete;
                if(createPersonWizard("Zu löschende Person angeben\n", &personToDelete) == 0){
                    (void)printf("Person wird gelöscht:\n");
                    prettyPrintPerson(&personToDelete);
                    removePerson(&personToDelete);
                }
            break;
            case Show:
                (void) printf("=====Show=====\n");
                printCurrentList();
            break;
            case Clear:
                (void) printf("=====Clear=====\n");
                (void) printf("#### ALLE PERSONEN GELÖSCHT ####\n");
                clearList();
            break;
            case End:
                (void) printf("=====Good Bye=====\n");
                run = false;
            break;
            default:
                (void) printf("Ungültige Eingabe\n");
            break;
        }
    } while (run);

    exit(EXIT_OK);
}
