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


int calcBitValue(int var, int pos) {
	return ((var) & (1<<(pos)));
}

int executeOneArgument(int arg1);
int executeTwoArguments(int arg1, int arg2);

int main(int argc, char* argv[])
{
	double MAX_VALUE = pow(2.0, sizeof(char) * 8) - 1;
	int arg1;
	int arg2;

	if (argc < 2) {
		(void)printf("Keine Argumente");
		return EXIT_FAILURE;
	}
	if (sscanf(argv[1], "%d", &arg1) < 1 || arg1 > MAX_VALUE) {
		(void)printf("Argument1: ungültiger Wert");
		return EXIT_FAILURE;
	}

	if (argc == 3) {
		if (sscanf(argv[2], "%d", &arg2) < 1 || arg1 < 7) {
			(void)printf("Argument2: ungültiger Wert");
			return EXIT_FAILURE;
		}
	}
	if (argc == 2) {
		executeOneArgument(arg1);
	} else {
		executeTwoArguments(arg1, arg2);
	}

}

int executeTwoArguments(int arg1, int arg2) {
	int bitValue = calcBitValue(arg1, arg2);
	int activateBitValue = arg1 | 1<<(arg2);
	int flipped = bitValue > 0 ? arg1-bitValue : activateBitValue;
	(void)printf("Your input: \t: %d\t0x%02x\t0%o\n", arg1, arg1, arg1);
	(void)printf("bit %d is %s set.\n", arg2, bitValue > 0 ? "" : "not");
	(void)printf("bit %d cleared: \t: %d\t0x%02x\t0%o\n", arg2, arg1-bitValue, arg1-bitValue, arg1-bitValue);
	(void)printf("bit %d set: \t\t: %d\t0x%02x\t0%o\n", arg2, activateBitValue, activateBitValue, activateBitValue);
	(void)printf("bit %d flipped: \t: %d\t0x%02x\t0%o\n", arg2, flipped, flipped, flipped);
}


int executeOneArgument(int arg1) {
	unsigned char value = (unsigned char)arg1;
	signed char signedValue = value;
	unsigned char addValue = value+255;
	signed char einer = (~value);
	signed char zweier = einer + 1;
	(void)printf("unsigned:\t %4u (0x%02x)\n", value, value);
	(void)printf("signed:\t\t %4d (0x%02x)\n", signedValue, signedValue);
	(void)printf("+255:\t\t %4d (0x%02x)\n", addValue, addValue);
	(void)printf("ones:\t\t %4d (0x%02x)\n", einer, einer);
	(void)printf("twos: \t\t %4d (0x%02x)\n", zweier, zweier);
	return EXIT_SUCCESS;
}
