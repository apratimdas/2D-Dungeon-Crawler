
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
		interfaceCombat();
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
	
	field_set_cell(x, y, FIELD_GROUND_CHAR); // prevents collision
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

	for (int i = 0; i < MAXMONSTERS; i++) {
		movemonsterdirection(i, rand() % 4);
	}
}

void monsterKill(int i) {
	
}

void interfaceCombat(void) {
	int damage = 0;

	for (int i = 0; i < MAXMONSTERS; i++) {
		// if player is within range of the monster
		if (util_distance(g_spawns[i].posx, g_spawns[i].posy, g_players[0].posx, g_players[0].posy) < 2) {
			damage = g_spawns[i].attack - g_players[0].defence;
			damage = damage < 0 ? 0 : damage;

			printf("%s attacks %s for %d points of damage (%d absorbed)!\n", g_spawns[i].name, g_players[0].name, damage, g_spawns[i].defence);
			g_players[0].healthpoints -= damage;
			printf("%s has %d healthpoints left.\n", g_players[0].name, g_players[0].healthpoints);

			if (g_players[0].healthpoints <= 0) {
				printf("%s is dead!\n", g_players[0].name);
				// game over
			}

			damage = g_players[0].attack - g_spawns[i].defence;
			damage = damage < 0 ? 0 : damage;

			printf("%s attacks %s for %d points of damage (%d absorbed)!\n", g_players[0].name, g_spawns[i].name, damage, g_players[0].defence);
			g_spawns[i].healthpoints -= damage;
			printf("%s has %d healthpoints left.\n", g_spawns[i].name, g_spawns[i].healthpoints);

			if (g_spawns[i].healthpoints <= 0) {
				printf("%s is dead!\n", g_spawns[i].name);
				// monster killed


			}
		}
	}
}

char keyActions(int index, int count[]) {
	char key;
	int row = g_players[index].posx,
		col = g_players[index].posy,
		isValidKey = 0;
	printf("\nPress a button to move (A = left, D = right, W = up, S = down).\n");
	printf("Press a SPACE to wait a turn.\n");
	printf("\nPress X to exit.\n");

	do {
		key = _getch();

		switch (key) {
		case 'A':
		case 'a':
		//case 75: // these numbers are for in case the key is int
			// consider if the player should use a turn if walking into an enemy space
			if (g_field[row][col - 1] == FIELD_GROUND_CHAR
				|| checkforladder(row, col - 1, count)) {
				g_players[index].posy = col - 1;
				isValidKey = 1;
			}
			break;
		case 'D':
		case 'd':
		//case 77:
			if (g_field[row][col + 1] == FIELD_GROUND_CHAR
				|| checkforladder(row, col + 1, count)) {
				g_players[index].posy = col + 1;
				isValidKey = 1;
			}
			checkforladder(row, col + 1, count);
			break;
		case 'W':
		case 'w':
		//case 72:
			if (g_field[row - 1][col] == FIELD_GROUND_CHAR
				|| checkforladder(row - 1, col, count)) {
				g_players[index].posx = row - 1;
				isValidKey = 1;
			}
			break;
		case 'S':
		case 's':
		//case 80:
			if (g_field[row + 1][col] == FIELD_GROUND_CHAR
				|| checkforladder(row + 1, col, count)) {
				g_players[index].posx = row + 1;
				isValidKey = 1;
			}
			break;
		case ' ': // wait turn
		case 'X': // exit
		case 'x':
			isValidKey = 1;
			break;
		}
	} while(!isValidKey);

	//Locks player cell
	field_set_cell(row, col, FIELD_GROUND_CHAR);
	field_set_cell(g_players[index].posx, g_players[index].posy, FIELD_BLOCK_CHAR);
	//Need to add monster movement here
	movemonsters();
	//Need to add monster collision conditions here
	
	return key;
}