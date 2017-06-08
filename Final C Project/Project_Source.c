
//#define _CRT_SECURE_NO_WARNINGS

#include "Project_Interface.h"

// checking for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>


/**
 *
 * @author Apratim, Matheus
 *
 * @brief This program (CII Project).
 *
 * @return 0 if everything executed correctly
 *
 */

int main (void) {
	start_game();
	//test_queue();
	//test();

	printf("Thank you for playing our game!\n");
	printf("We hope to see again soon.\n");
	printf("Best regards.\n");

	_CrtDumpMemoryLeaks();

    //getchar();
    getchar();
    return 0;
}