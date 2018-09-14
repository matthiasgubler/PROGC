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

#define ASCII_A 'A' ///< ASCII code of letter A
#define ASCII_1 '1' ///< ASCII code of digit 1

static void print_board(char board[8][8][3]) {
    // begin students to add code for task 4.1

    // print board (each field with leading space, including first field of each row).

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            (void) printf(" %s", board[row][col]);
        }
        (void) printf("\n");
    }

    // end students to add code
}

/**
 * @brief Main entry point.
 * @returns Returns EXIT_SUCCESS (=0) on success.
 */
int main(void) {
    // begin students to add code for task 4.1

    // define board variable (8x8 fields, each field has 3 chars)
    char board[8][8][3];

    // initialize each field according to task assignment description

    for (int row = 0; row < 8; ++row) {
        char rowCharacter = ASCII_1 + row;
        for (int col = 0; col < 8; ++col) {
            char colCharacter = ASCII_A + col;

            for (int charcount = 0; charcount < 3; ++charcount) {
                char currentCharacter;
                if (charcount == 0) {
                    currentCharacter = colCharacter;
                } else if (charcount == 1) {
                    currentCharactcler = rowCharacter;
                } else {
                    currentCharacter = '\0';
                }
                board[row][col][charcount] = currentCharacter;
            }
        }
    }

    // call print_board(board);
    print_board(board);
    // end students to add code

    return EXIT_SUCCESS;
}
