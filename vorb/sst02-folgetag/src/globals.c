//
// Created by Matthias Gubler on 14.09.18.
//

#include <stdio.h>
#include "globals.h"

bool isMonthInArray(Month month, Month monthArray[], int monthArraySize);

static Month monthsWith31Days[] = {Jan, Mar, May, Jul, Aug, Oct, Dec};

static Month monthsWith30Days[] = {Apr, Jun, Sep, Nov};

bool monthHas31Days(Month month) {
    return (isMonthInArray(month, monthsWith31Days, sizeof(monthsWith31Days) / sizeof(*monthsWith31Days)));
}

bool monthHas30Days(Month month) {
    return (isMonthInArray(month, monthsWith30Days, sizeof(monthsWith30Days) / sizeof(*monthsWith30Days)));
}

bool isMonthInArray(Month month, Month monthArray[], int monthArraySize) {
    for (int i = 0; i < monthArraySize; i++) {
        if (monthArray[i] == month) {
            return true;
        }
    }
    return false;
}

bool isLeapYear(int year) {
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        return true;
    } else {
        return false;
    }
}


int getPossibleDaysOfDate(Date *dateToCheck) {
    if (dateToCheck->month == Feb) {
        if (isLeapYear(dateToCheck->year) == true) {
            return 29;
        }
        return 28;
    }

    if (monthHas31Days(dateToCheck->month) == true) {
        return 31;
    }

    if (monthHas30Days(dateToCheck->month) == true) {
        return 30;
    }

    (void)printf("Ungültiger Input bei getPossibleDaysOfDate(Date*)\n");
    return -1;
}