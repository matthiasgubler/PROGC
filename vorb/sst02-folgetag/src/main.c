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
    Date parsed_date;

    if (validate_and_parse_date(argc, argv, &parsed_date) == 0) {
        addDay(&parsed_date);
        (void) printf("Neues Datum: %02d.%02d.%d\n", parsed_date.day, parsed_date.month, parsed_date.year);
    } else {
        (void) printf(
                "Aufruf des Programmes wie folgt: \"./sst02-folgetag 12 01 1993\" für die Berechnung des Datums 12.01.1993!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
