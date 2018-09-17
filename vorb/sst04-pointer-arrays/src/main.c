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


int readWords(char *wordList[], int* wordCounter);
int sort(char * words[], int size);


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
    char *wordList[100];
    int wordCounter = 0;
    if (!readWords(wordList, &wordCounter)) {
        printf("Fehler beim einlesen der Woerter..");
        return 0;
    }
    //sort(wordList, &wordCounter);
    //printf("wort ist: %s\n", wordList[0]);
    //printf("wort ist: %s\n", wordList[1]);
    //printf("wort ist: %s\n", wordList[2]);
    //printf("wort ist: %s\n", wordList[3]);
    return EXIT_SUCCESS;
}

int sort(char * words[], int size) {
    int swapCounter = 0;
    for (int x=1; x<=size-1; x++) {
        if (strcmp(words[x-1], words[x]) > 0) {
            char * temp = words[x];
            words[x] = words[x - 1];
            words[x-1] = temp;
            swapCounter++;
        }
    }
    if (swapCounter > 0) {
        sort(words, size);
    }
}

int readWords(char *wordList[], int *wordCounter) {
    char currentWord[20];
    int readInput = 1, counter=0, scanResult;
    size_t size;
    while (readInput) {
        (void) printf("Geben Sie ein Wort ein: ");
        scanResult = scanf("%s", currentWord);
        if (scanResult < 1) {
            printf("ungültiger Wert eingegeben");
            return 0;
        }
        if (strcmp(currentWord, "ZZZ") != 0) {
            *wordCounter = *wordCounter+1;
            size = strlen(currentWord);
            //char ist 1 byte immer, deshalb einfach size + 1.
            char *copyWord = malloc(size+1);
            if (copyWord == NULL) {
                printf("malloc Zuweisung failed...");
                return 0;
            }
            strncpy(copyWord, currentWord, size);
            *(wordList+counter) = copyWord;
            counter++;
        } else {
            readInput = 0;
        }
    }
    return 1;
}