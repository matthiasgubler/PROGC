//
// Created by Matthias Gubler on 14.09.18.
//

#include "process.h"

void addDays(Date *inputDate, int daysToAdd) {
    for (int i = 0; i < daysToAdd; ++i) {
        addDay(inputDate);
    }
}

void addDay(Date *inputDate) {
    int daysOfMonth = getPossibleDaysOfDate(inputDate);
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