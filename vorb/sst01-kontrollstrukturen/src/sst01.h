//
// Created by cod on 15.09.18.
//

#ifndef SST01_KONTROLLSTRUKTUREN_SST01_H
#define SST01_KONTROLLSTRUKTUREN_SST01_H
int executeAssignment1(int arg1);
int executeAssignment2(int arg1, int arg2);

struct Assignment1Result {
    unsigned char value;
    signed char signedValue;
    unsigned char addValue;
    signed char einer;
    signed char zweier;
};
struct Assignment1Result createAssignment1Result(int arg1);
#define MAX_ASS2 7
#endif //SST01_KONTROLLSTRUKTUREN_SST01_H
