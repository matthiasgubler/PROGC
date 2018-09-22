//
// Created by cod on 19.09.18.
//

#ifndef SST03_NOTENSTATISTIK_POINTER_H
#define SST03_NOTENSTATISTIK_POINTER_H
int readWords(char *wordList[], int* wordCounter);
int sort(char * words[], int size, int type);
void swapIt(char ** word1, char ** word2);
int wordExists(char *wordList[], const char *word);
int getSortType(int argc, char * type);
#define MAX_WORDS 100
#define MAX_STRING_LENGTH 20
#define STOP_WORD "ZZZ"
#endif //SST03_NOTENSTATISTIK_POINTER_H
