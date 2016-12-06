
#include "Project_Interface.h"
#include "Project_Monster.h"
#include "Project_Player.h"
#include "Project_Field.h"
#include "Project_Queue.h"
#include "Project_Util.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/**
 * test
 */

void test_queue(void) {
	queue *myq = NULL;
	qnode *tmp = NULL;
	monster m[3];
	monster *tmpmonster = NULL;

	m[0].speed = 10;
	m[1].speed = 12;
	m[2].speed = 11;

	myq = q_new();

	for (int i = 0; i < 3; i++) {
		q_insert(&myq, &m[i]);
	}
	tmp = myq->first;

	while (tmp != NULL) {
		printf("Test monster %d\n", tmp->data->speed);
		tmp = tmp->next;
	}

	q_cicle_queue(&myq);
	q_cicle_queue(&myq);

	for (int i = 0; i < 5; i++) {
		tmp = q_dequeue(&myq);

		if (tmp != NULL) {
			printf("Test monster %d\n", tmp->data->speed);
		}

		free(tmp);
		tmp = NULL;
	}

	q_delete(&myq);

	//free(myq);
}

void test(void) {
	int count[2];
	char choice;
	g_floor = 0;
	init_player();
	init_monster();
	read_file("field.txt", count);
	do {
		system("cls");
		printf("Name:\t%s\nHP:\t%d\nAttack:\t%d\n\n", g_players[0].name, g_players[0].healthpoints, g_players[0].attack);
		//print_field();
		print_viewport();
		printf("\nPress X to exit.\n");
		choice = keyActions(0, count);
		printf("%c\n", choice);
	} while (choice != 'X' && choice != 'x');
	delete_field();
}

//Need to add condition for blocked surrounding to prevent crash and collision detection with other monsters!!!
void movemonsterdirection(int i, int dir)
{
	srand(time(0));
	int x, y, flag = 0, ctr = 0, a, b;
	x = g_spawns[i].posx;
	y = g_spawns[i].posy;
	
	field_set_cell(x, y, FIELD_GROUND_CHAR);
	//testmdg
	//printf("M (%c) x = %d, y = %d, dist = %lf, %lf\n", g_spawns[i].character, x, y,
	//util_distance(x, y, g_players[0].posx, g_players[0].posy), util_distance(x+1, y, g_players[0].posx, g_players[0].posy));
	//do
	//{
	//	switch (dir)
	//	{
	//	case 0:
	//		if (g_field[x][y - 1] == FIELD_GROUND_CHAR)
	//		{
	//			g_spawns[i].posy = y = y - 1;
	//			flag = 1;
	//		}
	//		break;
	//	case 1:
	//		if (g_field[x][y + 1] == FIELD_GROUND_CHAR)
	//		{
	//			g_spawns[i].posy = y = y + 1;
	//			flag = 1;
	//		}
	//		break;
	//	case 2:
	//		if (g_field[x - 1][y] == FIELD_GROUND_CHAR)
	//		{
	//			g_spawns[i].posx = x = x - 1;
	//			flag = 1;
	//		}
	//		break;
	//	case 3:
	//		if (g_field[x + 1][y] == FIELD_GROUND_CHAR)
	//		{
	//			g_spawns[i].posx = x = x + 1;
	//			flag = 1;
	//		}
	//		break;
	//	case 4: // in case the monster choose to or cannot move
	//		flag = 1;
	//		break;
	//	}

	//	dir = rand() % 5;
	//} while (flag == 0);
	set_closest_distance(x, y, g_players[0].posx, g_players[0].posy, &a, &b);
	g_spawns[i].posx = x = a;
	g_spawns[i].posy = y = b;
	
	field_set_cell(x, y, FIELD_BLOCK_CHAR);
}

void movemonsters()
{
	srand(time(0));
	for (int i = 0; i < MAXMONSTERS; i++) movemonsterdirection(i, rand() % 4);
}

char keyActions(int index, int count[]) {
	char key;
	int row = g_players[index].posx,
		col = g_players[index].posy;
	printf("\nPress a button to move (A = left, D = right, W = up, S = down).\n");
	printf("Press a SPACE to wait a turn.\n");
	key = _getch();
	//Need to add monster movement here
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
	//Need to add monster collision conditions here
	field_set_cell(row, col, FIELD_GROUND_CHAR);
	field_set_cell(g_players[index].posx, g_players[index].posy, FIELD_BLOCK_CHAR);
	movemonsters();

	return key;
}