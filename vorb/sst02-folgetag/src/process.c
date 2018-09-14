//
// Created by Matthias Gubler on 14.09.18.
//

#include <stdio.h>
#include "process.h"

void subDay(Date *inputDate);

void addDays(Date *inputDate, int daysToAdd) {
    if (daysToAdd < 0) {
        for (int i = 0; i < (-1 * daysToAdd); ++i) {
            subDay(inputDate);
        }
    }

    for (int i = 0; i < daysToAdd; ++i) {
        addDay(inputDate);
    }
}

void addDay(Date *inputDate) {
    int daysOfMonth = getPossibleDaysOfDate(inputDate->month, inputDate->year);
    inputDate->day++;
    if (inputDate->day > daysOfMonth) {
        inputDate->day = 1;
        inputDate->month++;

        if (inputDate->month > Dec) {
            inputDate->month = Jan;
            inputDate->year++;
        }
    }
}

void subDay(Date *inputDate) {
    inputDate->day--;
    if (inputDate->day <= 0) {
        inputDate->month--;
        if (inputDate->month < Jan) {
            inputDate->month = Dec;
            inputDate->year--;
        }
        int daysLastOfMonth = getPossibleDaysOfDate(inputDate->month, inputDate->year);
        inputDate->day = daysLastOfMonth;
    }
}