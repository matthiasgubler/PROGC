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
#include "globals.h"
#include "process.h"
#include "validation.h"

#define EXIT_OK 0
#define IO_ERROR 1
#define BUFFER_ERROR 3

#define CONSOLE_BUFFER_SIZE 256

char cIO_OK = 0;
char caInternalBuffer[CONSOLE_BUFFER_SIZE];

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
    int day, month, year, daysToAdd;

    do {
        Date parsed_date;
        (void) printf("\nEingabe des Datums im Format DD MM YYYY [Plus Anz Tage]\n");

        if (fgets(caInternalBuffer, CONSOLE_BUFFER_SIZE, stdin) == NULL) {
            exit(IO_ERROR);
        }

        int scannedParams = sscanf(caInternalBuffer ,"%d %d %d %d", &day, &month, &year, &daysToAdd);

        if(scannedParams == EOF){
            exit(BUFFER_ERROR);
        }

        if (validate_and_parse_date(scannedParams, day, month, year, &parsed_date) == 0) {
            if (scannedParams == 4) {
                addDays(&parsed_date, daysToAdd);
            } else {
                addDay(&parsed_date);
            }

            (void) printf("Neues Datum: %02d.%02d.%d\n", parsed_date.day, parsed_date.month, parsed_date.year);
        } else {
            (void) printf(
                    "Eingabe des Datums wie folgt: \"12 01 1993\" für die Berechnung des Datums 12.01.1993!\n");
        }
    } while (cIO_OK == 0);

    exit(EXIT_OK);
}
