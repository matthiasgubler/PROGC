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
#include <string.h>

/**
 * @brief   swaps two characters at the given addresses.
 * @param[in] a  the location of 1st character
 * @param[in] b  the location of 2nd character
 */
void swap_char(char *a, char *b) {
	// begin students to add code for task 4.1
	char temp = *a;
	*a = *b;
	*b = temp;
	// end students to add code
}

/**
 * @brief              Reverses buffer content inplace.
 * @param[in] buffer   The buffer to process.
 * @return             The passed buffer.
 */
char *reverse(char buffer[]) {
	// begin students to add code for task 4.1
	int bufferlen = strlen(buffer);

	for (int i = 0; i < bufferlen/2; ++i) {
        swap_char(&buffer[i], &buffer[bufferlen-1-i]);
	}
	
	// end students to add code
	return buffer;
}


/**
 * @brief Main entry point.
 * @returns Returns EXIT_SUCCESS (=0) on success.
 */
int main(void)
{
	char buffer[] = "Hello";
	(void)printf("%s --> ", buffer);
	(void)printf("%s\n", reverse(buffer));
	return EXIT_SUCCESS;
}
