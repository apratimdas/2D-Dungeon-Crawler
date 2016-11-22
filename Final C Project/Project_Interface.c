
#include "Project_Interface.h"
#include "Project_Monster.h"
#include "Project_Player.h"
#include "Project_Field.h"
#include "Project_Queue.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/**
 * 
 */

void test_queue(void) {
	queue *myq;
	qnode *tmp = NULL;
	monster m[3];

	m[0].speed = 10;
	m[1].speed = 12;
	m[2].speed = 11;

	myq = (queue*)malloc(sizeof(qnode));

	myq->first = myq->last = NULL;

	qinsert(&myq, &m[1]);
	/*tmp = myq->first;

	while (tmp != NULL) {
		printf("Test monster %d\n", tmp->data->speed);
		tmp = tmp->next;
	}

	qdelete(&myq);*/

	free(myq);

	printf("Thank you for using my program!\n");
	printf("Best regards.\n");
}

void test(void) {
	int count[2];
	char choice;
	floor = 0;
	read_file("field.txt", count);
	do {
		system("cls");
		print_viewport();
		printf("\nPress X to exit.\n");
		choice = keyActions(0, count);
		printf("%c\n", choice);
	} while (choice != 'X' && choice != 'x');
	delete_field();

	printf("Thank you for using my program!\n");
	printf("Best regards.\n");
}

char keyActions(int index, int count[]) {
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
		checkforladder(row, col - 1, count);
		break;
	case 'D':
	case 'd':
	case 77:
		g_players[index].posy = (g_field[row][col + 1] == FIELD_GROUND_CHAR) ? col + 1 : col;
		checkforladder(row, col + 1, count);
		break;
	case 'W':
	case 'w':
	case 72:
		g_players[index].posx = (g_field[row - 1][col] == FIELD_GROUND_CHAR) ? row - 1 : row;
		checkforladder(row-1, col, count);
		break;
	case 'S':
	case 's':
	case 80:
		g_players[index].posx = (g_field[row + 1][col] == FIELD_GROUND_CHAR) ? row + 1 : row;
		checkforladder(row+1, col, count);
		break;
	}

	return key;
}