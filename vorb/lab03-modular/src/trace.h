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
/**
 * @file
 * @brief Lab implementation
 */
// begin students to add code for task 4.2
#define TRACE(MSG, ...) \
 do { \
 fprintf(stderr, \
 "TRACE: " MSG "\n", \
 ##__VA_ARGS__); \
 } while(0)
// end students to add code
