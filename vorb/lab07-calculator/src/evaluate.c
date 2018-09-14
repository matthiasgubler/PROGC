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
#include <assert.h>
#include <stdio.h>
#include "evaluate.h"

// begin students to add code for task 4.1
static double nop(double v) {
    return v;
}

static double neg(double v) {
    return -v;
}

static double add(double a, double b) {
    return a + b;
}

static double sub(double a, double b) {
    return a - b;
}

static double mul(double a, double b) {
    return a * b;
}

static double div(double a, double b) {
    return a / b;
}
// end students to add code


/// map for unary functions
struct unaryLookup {
    char op; ///< operato as key
    // begin students to add code for task 4.1
    double (*exec)(double);
    // end students to add code
};

/// map for binary functions
struct binaryLookup {
    char op; ///< operator as key
    // begin students to add code for task 4.1
    double (*exec)(double, double);
    // end students to add code
};

/// lookup table for unary operations
static struct unaryLookup unaryLookupTable[] = {
        // begin students to add code for task 4.1
        {PLUS, nop},
        {MINUS, neg}
        // end students to add code
};

/// lookup table for binary operations
static struct binaryLookup binaryLookupTable[] = {
        // begin students to add code for task 4.1
        {ADD, add},
        {SUB, sub},
        {DIV, div},
        {MUL, mul}
        // end students to add code
};

double evaluateUnaryOp(char op, double right) {
    // begin students to add code for task 4.1
    for (int i = 0; i < sizeof(unaryLookupTable)/sizeof(*unaryLookupTable); ++i) {
        struct unaryLookup unaryLookupElement = unaryLookupTable[i];
        if(unaryLookupElement.op == op){
            return unaryLookupElement.exec(right);
        }else if(op < 32){
            return nop(right);
        }
    }
    // end students to add code
    printf("Meeeeeh unary op: %d ... right: %f ", op, right);
    assert(!"unexpected operator");
}

double evaluateBinaryOp(char op, double left, double right) {
    // begin students to add code for task 4.1
    for (int i = 0; i < sizeof(binaryLookupTable)/sizeof(*binaryLookupTable); ++i) {
        struct binaryLookup binaryLookupElement = binaryLookupTable[i];
        if(binaryLookupElement.op == op){
            return binaryLookupElement.exec(left, right);
        }
    }
    // end students to add code
    printf("Meeeeeh binary op: %d ... left: %f ... right: %f ", op, left, right);
    assert(!"unexpected operator");
}


