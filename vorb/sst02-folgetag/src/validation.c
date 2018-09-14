//
// Created by Matthias Gubler on 14.09.18.
//

#include <stdio.h>
#include "validation.h"
#include "globals.h"

#define PARSE_ERROR -1
#define GREGORIAN_CAL_START_YEAR 1583

bool isValidInputInt(int intToVerify, char *errorText);

bool isDateValid(Date *parsed_date);

int validate_and_parse_date(int scannedParams, int day, int monthPreChecked, int year, Date *parsed_date) {
    Month month;

    if (scannedParams < 3 && scannedParams > 4) {
        (void) printf("Anzahl Argumente ungültig!\n");
        return PARSE_ERROR;
    }

    if (isValidInputInt(day, "Tag") == false
        || isValidInputInt(monthPreChecked, "Monat") == false
        || isValidInputInt(year, "Jahr") == false) {
        return PARSE_ERROR;
    }

    if (year < GREGORIAN_CAL_START_YEAR) {
        (void) printf("Es können nur Daten ab dem 1. Januar %d eingegeben werden!\n", GREGORIAN_CAL_START_YEAR);
        return PARSE_ERROR;
    }

    if (monthPreChecked >= Jan && monthPreChecked <= Dec) {
        month = (Month) monthPreChecked;
    } else {
        (void) printf("Monat muss Wert von 1 - 12 haben!\n");
        return PARSE_ERROR;
    }

    *parsed_date = (Date) {day, month, year};

    if (isDateValid(parsed_date) == false) {
        return PARSE_ERROR;
    }

    return 0;
}

bool isDateValid(Date *parsed_date) {
    if (parsed_date->month == Feb) {
        if (parsed_date->day <= 28) {
            return true;
        } else if (parsed_date->day == 29) {
            if (isLeapYear(parsed_date->year) == true) {
                return true;
            }

            (void) printf("Kein Schaltjahr: Die Anzahl Tage ist zu gross\n");
            return false;
        } else {
            (void) printf("Die Anzahl Tage ist zu gross\n");
            return false;
        }
    }

    if (monthHas31Days(parsed_date->month) == true && parsed_date->day <= 31) {
        return true;
    }

    if (monthHas30Days(parsed_date->month) == true && parsed_date->day <= 30) {
        return true;
    }

    (void) printf("Die Anzahl Tage ist zu gross\n");
    return false;
}

bool isValidInputInt(int intToVerify, char *errorText) {
    if (intToVerify <= 0) {
        (void) printf("Argument '%s' ist negativ!\n", errorText);
        return false;
    }
    return true;
}
