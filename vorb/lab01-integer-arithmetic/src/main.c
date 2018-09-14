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


int evaluateXCHF(int *betrag, int betragToEvaluate);
void printfCountBetrag(int count, char* betragString);

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments
 *                  with argv[0] being the command call
 *                  argv[1] the 1st argument, ...
 *                  argv[argc-1] the last argument.
 * @returns Returns the rest of the calculation or
 *                  255 on failure
 */
int main(int argc, char* argv[])
{
	// begin students to add code for task 4.2
	int betrag;
	if(argc == 2 && sscanf(argv[1], "%d", &betrag) == 1 && betrag > 0){
        printf("CHF %2.2f:\n", betrag/100.0);
        printfCountBetrag(evaluateXCHF(&betrag, 500), "5.00");
        printfCountBetrag(evaluateXCHF(&betrag, 200), "2.00");
        printfCountBetrag(evaluateXCHF(&betrag, 100), "1.00");
        printfCountBetrag(evaluateXCHF(&betrag, 50), "0.50");
        printfCountBetrag(evaluateXCHF(&betrag, 20), "0.20");
        printfCountBetrag(evaluateXCHF(&betrag, 10), "0.10");
        printfCountBetrag(evaluateXCHF(&betrag, 5), "0.05");
        if(betrag == 0){
            printf("Kein Rest\n");
        }else{
            printf("Rest = %2.2f\n", betrag/100.0);
        }

	}else{
		printf("Input ist nicht ganzzahlig\n");
		return 255;
	}

	// end students to add code
	return betrag; // rest = 0 = success
}

int evaluateXCHF(int *betrag, int betragToEvaluate){
    int count = 0;
    while(*betrag >= betragToEvaluate){
        count++;
        *betrag = *betrag - betragToEvaluate;
    }

    return count;
}


void printfCountBetrag(int count, char* betragString){
    printf("- %d x %s\n", count, betragString);
}