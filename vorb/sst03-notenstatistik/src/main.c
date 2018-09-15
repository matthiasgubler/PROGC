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
#include <math.h>

int readPoints(int *punkte);
int readMinimum(int *minimum);


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
int main(int argc, char* argv[])
{
    int minimum6;
	int punkte[100] = {0};
	readPoints(punkte);
    readMinimum(&minimum6);
    return EXIT_SUCCESS;
}

int readMinimum(int *minimum) {
    printf("Wieviele punkte fuer eine 6?: ");
    int minimumValid = scanf("%u", minimum);
    if (minimumValid < 1) {
        printf("Sie haben einen ungueltigen maximum-wert eingegeben");
        return 0;
    }
    return 1;
}

int readPoints(int *punkte) {
    int c, readInput = 1, counter=0;
    while (readInput) {
        printf("Geben Sie die erreichte Punktzahl ein: ");
        readInput = scanf("%u", &c);
        if (readInput && c >= -1) {
            if (c == -1) {
                readInput = 0;
            } else {
                *(punkte + counter++) = c;
            }
        } else {
            printf("Sie haben einen ungueltigen Wert eingegeben");
            return 0;
        }
    }
    return 1;
}


