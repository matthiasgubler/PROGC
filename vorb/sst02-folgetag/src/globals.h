//
// Created by Matthias Gubler on 14.09.18.
//

#include <stdbool.h>

#ifndef PROGC_GLOBALS_H
#define PROGC_GLOBALS_H

typedef enum {
    Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
} Month;

typedef struct {
    int day;
    Month month;
    int year;
} Date;

bool monthHas31Days(Month month);

bool monthHas30Days(Month month);

bool isLeapYear(int year);

int getPossibleDaysOfDate(Month month, int year);

#endif //PROGC_GLOBALS_H


