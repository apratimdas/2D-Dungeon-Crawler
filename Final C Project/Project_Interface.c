
#include "Project_Interface.h"
#include "Project_Player.h"
#include "Project_Field.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/**
 * 
 */

void test(void) {
	int count[2];
	char choice;

	read_file("field.txt", count);

	printf("Test %d %d\n", count[0], count[1]);

	do {
		system("cls");
		print_viewport();
		printf("\nPress X to exit.\n");
		choice = keyActions(0);
		printf("%c\n", choice);
	} while (choice != 'X' && choice != 'x');
	delete_field();

	printf("Thank you for using my program!\n");
	printf("Best regards.\n");
}

char keyActions(int index) {
	char key;
	int row = g_players[index].posx,
		col = g_players[index].posy;
	printf("\nPress a button to move (A = left, D = right, W = up, S = down).\n");
	printf("Press a SPACE to wait a turn.\n");
	key = _getch();

	switch (key) {
	case 'A':
	case 'a':
	case 75:
		g_players[index].posy = (g_field[row][col - 1] == FIELD_GROUND_CHAR) ? col - 1 : col;
		break;
	case 'D':
	case 'd':
	case 77:
		g_players[index].posy = (g_field[row][col + 1] == FIELD_GROUND_CHAR) ? col + 1 : col;
		break;
	case 'W':
	case 'w':
	case 72:
		g_players[index].posx = (g_field[row - 1][col] == FIELD_GROUND_CHAR) ? row - 1 : row;
		break;
	case 'S':
	case 's':
	case 80:
		g_players[index].posx = (g_field[row + 1][col] == FIELD_GROUND_CHAR) ? row + 1 : row;
		break;
	}

	return key;
}