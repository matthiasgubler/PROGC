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
#include <string.h>
#include "pointer.h"

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
    char *wordList[MAX_WORDS] = {0};
    int wordCounter = 0;
    if (!readWords(wordList, &wordCounter)) {
        printf("Fehler beim einlesen der Woerter..");
        return 0;
    }
    sort(wordList, wordCounter, getSortType(argc, argv[1]));
    for (int x = 0; x < 50; x++) {
        if (wordList[x] != NULL) {
            printf("%s\n", wordList[x]);
        }
    }
    return EXIT_SUCCESS;
}

int getSortType(int argc, char * type) {
    if (argc > 1) {
        return strcmp("desc", type) == 0 ? 1 : 0;
    }
    return 0;
}

/**
 * bubble-sort weil am einfachsten, zum swappen von pointern;
 * @param words
 * @param size
 * @return
 */
int sort(char * words[100], int size, int type) {
    int swapCounter = 0;
    for (int x=1; x<=size-1; x++) {
        if (type == 0) {
            if (strcmp(words[x-1], words[x]) > 0) {
                swapIt(&words[x], &words[x-1]);
                swapCounter++;
            }
        } else {
            if (strcmp(words[x-1], words[x]) < 0) {
                swapIt(&words[x], &words[x-1]);
                swapCounter++;
            }
        }

    }
    if (swapCounter > 0) {
        sort(words, size, type);
    }
    return 1;
}

void swapIt(char ** word1, char ** word2) {
    char * temp = *word1;
    *word1 = *word2;
    *word2 = temp;
}

int wordExists(char *wordList[], const char *word) {
    for (int x=0; x<MAX_WORDS; x++) {
        if (wordList[x] != NULL) {
            if (strcmp(wordList[x], word) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int readWords(char *wordList[], int *wordCounter) {
    char currentWord[MAX_STRING_LENGTH + 1] = {0};
    currentWord[20] = '\0';
    int readInput = 1, counter=0, scanResult;
    size_t size;
    while (readInput) {
        (void) printf("Geben Sie ein Wort ein: ");
        (void) fgets(currentWord, 21, stdin);
        strtok(currentWord, "\n");
        scanResult = 1;
        if (scanResult < 1) {
            printf("ungültiger Wert eingegeben");
            return 0;
        }
        else if (strcmp(currentWord, STOP_WORD) != 0 && *wordCounter < MAX_WORDS-1) {
            if (wordCounter <= 0 || !wordExists(wordList, currentWord)) {
                *wordCounter = *wordCounter+1;
                size = strlen(currentWord);
                //char ist 1 byte immer, deshalb einfach size + 1.
                char * copyWord = malloc(size+1);
                if (copyWord == NULL) {
                    printf("malloc Zuweisung failed...");
                    return 0;
                }
                strncpy(copyWord, currentWord, size);
                *(wordList+counter) = copyWord;
                counter++;
            }
        } else {
            readInput = 0;
        }
    }
    return 1;
}