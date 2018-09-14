/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include "read.h"
#include "trace.h"

#define PARSE_ERROR -1
#define ASCII_SPACE 32
#define ASCII_DIGIT_0 48
#define ASCII_DIGIT_9 57
#define NO_POS -1
#define BUFFERSIZE 10
/**
 * @file
 * @brief Lab implementation
 */
// begin students to add code for task 4.1
int getInt(int maxResult) {
    TRACE("getInt(%d)", maxResult);
    char buffer[BUFFERSIZE];

    int result = 0;

    // read line: up to EOL or EOF (i.e. error while reading)
    char inputString[256];

    int scannedParams = scanf("%s", inputString);
    int bytes = strlen(inputString);

    if (scannedParams < 0) { // only buffer first n characters
        return READ_ERROR; // exceed buffer size, continue read line
    }

    if (bytes < BUFFERSIZE && bytes > 0 && scannedParams > 0) { // only buffer first n characters
        (void)strcpy(buffer, inputString);
    } else {
        return PARSE_ERROR; // exceed buffer size, continue read line
    }

    // check for numbers: skip leading and trailing spaces
    // (i.e. this includes all control chars below the space ASCII code)
    int pos = 0;
    while ((pos < bytes) && (buffer[pos] <= ASCII_SPACE)) pos++; // skip SP

    int posOfFirstDigit = pos;
    int posOfLastDigit = NO_POS;
    while ((pos < bytes)
           && (buffer[pos] >= ASCII_DIGIT_0)
           && (buffer[pos] <= ASCII_DIGIT_9)) {
        posOfLastDigit = pos;
        pos++;
    }
    while ((pos < bytes) && (buffer[pos] <= ASCII_SPACE)) pos++; // skip SP
    // produce return value
    if (result != 0) {
        // previously detected read or parse error given
    } else if ((pos != bytes) || (posOfLastDigit == NO_POS)) {
        return PARSE_ERROR;
    } else { // convert number
        for (int i = posOfFirstDigit; i <= posOfLastDigit; i++) {
            result = result * 10 + (buffer[i] - ASCII_DIGIT_0);
            if (result > maxResult) {
                return PARSE_ERROR;
            }
        }
    }
    return result;
}

// end students to add code
