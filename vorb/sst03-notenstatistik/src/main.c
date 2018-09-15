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
#include "stats.h"



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
    int minimum6, moreEqualFour;
	int punkte[100] = {0}, noten[100] = {0};
	struct MarkCounter counter = {0, 0, 0, 0, 0, 0};
	if (!readPoints(punkte)) {
	    return EXIT_FAILURE;
	}
    if (!readMinimum(&minimum6)) {
        return EXIT_FAILURE;
    }
    (void)calculateStatistics(punkte, noten, minimum6, &counter);

    moreEqualFour = counter.vierer + counter.fuenfer + counter.sechser;
    (void) printf("Statistics (%d Students, %d points needed for mark 6):\n", countStudents(&counter), minimum6);
    (void) printf("Mark 6: %d\n", counter.sechser);
    (void) printf("Mark 5: %d\n", counter.fuenfer);
    (void) printf("Mark 4: %d\n", counter.vierer);
    (void) printf("Mark 3: %d\n", counter.dreier);
    (void) printf("Mark 2: %d\n", counter.zweier);
    (void) printf("Mark 1: %d\n\n", counter.einer);
    (void) printf("Best mark: \t\t%d\n", findBestMark(&counter));
    (void) printf("Worst mark: \t%d\n", findWorstMark(&counter));
    (void) printf("Average mark: \t%0.2f\n", calcAverage(&counter));
    (void) printf("Mark >= 4: \t\t%d\n", moreEqualFour);
    return EXIT_SUCCESS;
}


double calcAverage(const struct MarkCounter* counter) {
    return ((*counter).einer +
           (*counter).zweier * 2.0 +
           (*counter).dreier * 3.0 +
           (*counter).vierer * 4.0 +
           (*counter).fuenfer * 5.0 +
           (*counter).sechser * 6.0) / countStudents(counter);
}

int countStudents(const struct MarkCounter* counter) {
   return (*counter).einer +
   (*counter).zweier +
   (*counter).dreier +
   (*counter).vierer +
   (*counter).fuenfer +
   (*counter).sechser;
}

int findWorstMark(const struct MarkCounter* counter) {
    if ((*counter).zweier > 0) {
        return 2;
    }
    if ((*counter).dreier > 0) {
        return 3;
    }
    if ((*counter).vierer > 0) {
        return 4;
    }
    if ((*counter).fuenfer > 0) {
        return 5;
    }
    if ((*counter).sechser > 0) {
        return 6;
    }
    return 1;
}

int findBestMark(const struct MarkCounter* counter) {
    if ((*counter).fuenfer > 0) {
        return 5;
    }
    if ((*counter).vierer > 0) {
        return 4;
    }
    if ((*counter).dreier > 0) {
        return 3;
    }
    if ((*counter).zweier > 0) {
        return 2;
    }
    if ((*counter).einer > 0) {
        return 1;
    }
    return 6;
}

int calculateStatistics(const int *punkte, int *noten, int minimum6, struct MarkCounter *counter) {
    for (int x=0 ; x<100; x++) {
        *(noten + x) = calcNote(*(punkte + x), minimum6);
        if (*(noten + x) > 6) {
            *(noten + x) = 6;
        }
        switch(*(noten + x)) {
            case 1: (*counter).einer = (*counter).einer+1; break;
            case 2: (*counter).zweier = (*counter).zweier+1; break;
            case 3: (*counter).dreier = (*counter).dreier+1; break;
            case 4: (*counter).vierer = (*counter).vierer+1; break;
            case 5: (*counter).fuenfer = (*counter).fuenfer+1; break;
            case 6: (*counter).sechser = (*counter).sechser+1; break;
        }
    }
    return 1;
}

int calcNote(int punkte, int punkteFuer6) {
    if (punkte == 0) {
        return 0;
    }
    return (int) round(1 + ((5.0 * punkte) /punkteFuer6));
}

int readMinimum(int *minimum) {
    (void) printf("Wieviele punkte fuer eine 6?: ");
    int minimumValid = scanf("%u", minimum);
    if (minimumValid < 1) {
        (void) printf("Sie haben einen ungueltigen maximum-wert eingegeben");
        return 0;
    }
    return 1;
}

int readPoints(int *punkte) {
    int c, readInput = 1, counter=0;
    while (readInput) {
        (void) printf("Geben Sie die erreichte Punktzahl ein: ");
        readInput = scanf("%u", &c);
        if (readInput && (c > 0 || c == -1)) {
            if (c == -1) {
                readInput = 0;
            } else {
                *(punkte + counter++) = c;
            }
        } else {
            (void)printf("Sie haben einen ungueltigen Wert eingegeben");
            return 0;
        }
    }
    return 1;
}


