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


int main(int argc, char* argv[])
{
	double MAX_VALUE = pow(2.0, sizeof(char) * 8) - 1;
	int valueTemp;

	if (sscanf(argv[1], "%u", &valueTemp) < 1 || valueTemp > MAX_VALUE) {
		(void)printf("ungültiger wert");
		return EXIT_FAILURE;
	}
	unsigned char value = valueTemp;
	signed char signedValue = value;
	unsigned char addValue = value+255;
	signed char einer = (~value);
	signed zweier = einer + 1;

	printf("unsigned:\t %4u (0x%02x)\n", value, value);
	printf("signed:\t\t %4d (0x%02x)\n", signedValue, signedValue);
	printf("+255:\t\t %4d (0x%02x)\n", addValue, addValue);
	printf("ones:\t\t %4d (0x%02x)\n", einer, einer);
	printf("twos: \t\t %4d (0x%02x)\n", zweier, zweier);
	return EXIT_SUCCESS;

	/*
	 * 8 = 1000
	 * 15 = 1111
	 *
	 */
}
