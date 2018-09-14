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
 * @brief  point structure of double coordinates
 */
// begin students to add code for task 4.1

typedef struct {
	double x, y;
} Point2D;

// end students to add code


/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments,
 *                  with argv[0] being the command call,
 *                  argv[1] the 1st argument,
 *                  argv[argc-1] the last argument.
 * @returns Returns EXIT_SUCCESS (=0) on success.
 */
int main(int argc, char* argv[])
{
	double distance = 0.0;
// begin students to add code for task 4.2

	// parse arguments with error handling
	double point1X;
	double point1Y;
	double point2X;
	double point2Y;

	Point2D point1;
	Point2D point2;


	if (argc != 5) {
		return EXIT_FAILURE;
	}

	if (sscanf(argv[1], "%lf", &point1X) == 1
		&& sscanf(argv[2], "%lf", &point1Y) == 1
		&& sscanf(argv[3], "%lf", &point2X) == 1
		&& sscanf(argv[4], "%lf", &point2Y) == 1) {
		// make one line variable an initialize from the parsed arguments
		point1 = (Point2D){point1X, point1Y};
		point2 = (Point2D){point2X, point2Y};
	} else {
		return EXIT_FAILURE;
	}


	// print the line variable in the following format:
m	distance = sqrt(pow(point1.x - point2.x, 2)+pow(point1.y - point2.y, 2));

	// end students to add code
	(void)printf("distance = %g\n", distance);

	return EXIT_SUCCESS;


}
