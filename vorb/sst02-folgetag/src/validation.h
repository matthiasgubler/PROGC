//
// Created by Matthias Gubler on 14.09.18.
//

#ifndef PROGC_VALIDATION_H
#define PROGC_VALIDATION_H

#include "globals.h"

#define NO_PARSE_ERROR 0
#define PARAM_COUNT_ERROR -1
#define INVALID_DMY_ERROR -2
#define INVALID_GREGORIAN_YEAR_ERROR -3
#define INVALID_MONTH_ERROR -4
#define INPUT_DATE_INVALID_ERROR -5

int validate_and_parse_date(int scannedParams, int day, int month, int year, Date *parsed_date);

#endif //PROGC_VALIDATION_H
