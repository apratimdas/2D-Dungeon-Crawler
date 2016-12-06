
#include "Project_Field.h"

#include "Project_Util.h"
#include "Project_Player.h" // for starting position
//#include "Project_Monster.h" // for initial monster spawns

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


#define VIEWPORT_SIZE 5

/**
 * Test
 */

void monsterspawner();
void resetmonsters();

void read_file(const char *file_name, int count[]) {
    FILE *myfile;
    int rows = 0; 
    int cols = 0; 
    char ch;

    if((myfile = fopen(file_name, "r")) == NULL) {
        printf("Cannot open file.\n");
		getchar();
        exit(1);
    }

    while(!feof(myfile)) {
        ch = fgetc(myfile);
        if(ch == '\n') {
            rows++;
        } else if (rows == 0) {
            cols++;
        }
    }

    rewind(myfile);

    count[0] = g_rows = rows;
    count[1] = g_cols = cols;

    g_field = (char**)malloc(sizeof(char*) * g_rows);

    for (int i = 0; i < g_rows; i++) {
        g_field[i] = (char*)malloc(sizeof(char) * g_cols);
    }

    for (int i = 0; i < g_rows; i++) {
        for (int j = 0; j < g_cols; j++) {
            g_field[i][j] = '0';
        }
    }

    rows = 0;
    cols = 0;

    while(!feof(myfile)) {
        ch = fgetc(myfile);

        if(ch == '\n') {
            cols = 0;
            rows++;
        } else if (rows < g_rows) {
			if (ch == 'S') {
				g_field[rows][cols] = FIELD_GROUND_CHAR;

				for (int i = 0; i < MAXPLAYERS; i++) {
					g_players[i].posx = rows; // maybe create set functions
					g_players[i].posy = cols;

					field_set_cell(rows, cols, FIELD_BLOCK_CHAR);
					//printf("%d, %d, %d\n", rows, cols, g_players[i].posx);
				}
			}
			else {
				g_field[rows][cols] = ch;
			}
            cols++;
        }
    }

	g_viewport_size = VIEWPORT_SIZE;
	resetmonsters();
	monsterspawner();
}

void resetmonsters()
{
	/*for (int i = 0; i < MAXMONSTERS; i++)
	{
		g_monsters[i].posx = -1;
		g_monsters[i].posy = -1;
	}*/

	qnode *tmp = g_turn_order->first;

	while (tmp != NULL) {
		if (tmp->data) {
			tmp->data->posx = -1;
			tmp->data->posy = -1;
		}
		tmp = tmp->next;
	}
}

//Need to modify spawn location here
void monsterspawner()
{
	monster *mon;
	int i, j, r, ctr = 0;

	srand(time(0));

	do
	{
		i = rand() % g_rows;
		j = rand() % g_cols;
		if (g_field[i][j] != '1');
		else
		{
			r = rand();
			if ((r % 15) >= 0 && (r % 15) <= 4)
			{
				////set monster with freq 5
				//g_monsters[3].posx = i;
				//g_monsters[3].posy = j;
				////g_field[i][j] = g_monsters[3].character;
				//copymonsterspawns(ctr, 3);
				//printf("Monster 1\n");

				mon = create_rat();
				mon->posx = i;
				mon->posy = j;
			}
			else if ((r % 15) >= 5 && (r % 15) <= 8)
			{
				////freq 4
				//g_monsters[0].posx = i;
				//g_monsters[0].posy = j;
				////g_field[i][j] = g_monsters[0].character;
				//copymonsterspawns(ctr, 0);
				//printf("Monster 2\n");

				mon = create_imp();
				mon->posx = i;
				mon->posy = j;
			}
			else if ((r % 15) >= 9 && (r % 15) <= 11)
			{
				//g_monsters[4].posx = i;
				//g_monsters[4].posy = j;
				////g_field[i][j] = g_monsters[4].character;
				//copymonsterspawns(ctr, 4);
				//printf("Monster 3\n");

				mon = create_thief();
				mon->posx = i;
				mon->posy = j;
			}
			else if ((r % 15) >= 12 && (r % 15) <= 13)
			{
				//g_monsters[2].posx = i;
				//g_monsters[2].posy = j;
				////g_field[i][j] = g_monsters[2].character;
				//copymonsterspawns(ctr, 2);
				//printf("Monster 4\n");

				mon = create_ogre();
				mon->posx = i;
				mon->posy = j;
			}
			else
			{
				//g_monsters[1].posx = i;
				//g_monsters[1].posy = j;
				////g_field[i][j] = g_monsters[1].character;
				//copymonsterspawns(ctr, 1);
				//printf("Monster 5\n");

				mon = create_daemon();
				mon->posx = i;
				mon->posy = j;
			}

			q_insert(&g_turn_order, mon);
			ctr++;
		}

	} while (ctr < 5);
}

bool checkformonster(int x, int y)
{
	/*for (int i = 0; i < MAXMONSTERS; i++) {
		if (x == g_spawns[i].posx && y == g_spawns[i].posy) {
			return true;
		}
	}*/
	qnode *tmp = g_turn_order->first;

	while (tmp != NULL) {
		if (tmp->data) {
			if (x == tmp->data->posx && y == tmp->data->posy) {
				return true;
			}
		}
		tmp = tmp->next;
	}

	return false;
}

//int getmonsterindex(int x, int y)
//{
//	qnode *tmp = g_turn_order->first;
//
//	while (tmp != NULL) {
//		if (tmp->data) {
//			if (x == tmp->data->posx && y == tmp->data->posy) {
//				return i;
//			}
//		}
//	}
//
//	return -1;
//
//	//for (int i = 0; i < MAXMONSTERS; i++) if (x == g_spawns[i].posx && y == g_spawns[i].posy) return i;
//}

monster* getmonster(int x, int y)
{
	qnode *tmp = g_turn_order->first;

	while (tmp != NULL) {
		if (tmp->data) {
			if (x == tmp->data->posx && y == tmp->data->posy) {
				return tmp->data;
			}
		}
		tmp = tmp->next;
	}

	return NULL;

	//for (int i = 0; i < MAXMONSTERS; i++) if (x == g_spawns[i].posx && y == g_spawns[i].posy) return i;
}

bool field_is_valid_pos(int x, int y) {
	return (x < g_rows && x >= 0 && y < g_cols && y >= 0);
}

void field_set_cell(int x, int y, char ch) {
	if (field_is_valid_pos(x, y)) {
		g_field[x][y] = ch;
	}
}

void print_field(void) {
	for (int i = 0; i < g_rows; i++) {
		for (int j = 0; j < g_cols; j++) {
			if (checkformonster(i, j)) {
				//add color
				//SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_RED);
				printf("%c", g_field[i][j]);
				//SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (i == g_players[0].posx && j == g_players[0].posy) {
				printf("%c", PLAYERMARKER);
			}
			else if (g_field[i][j] == '0' || g_field[i][j] == '1' || g_field[i][j] == 'S') {
				//printf(" ");
				printf("%c", g_field[i][j]);
			}
			else {
				//SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_RED);
				printf("%c", g_field[i][j]);
			}
		}

		printf("\n");
	}
}

void print_viewport(void) {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	int size = g_viewport_size,
		row = g_players[0].posx,
		col = g_players[0].posy;

	/*for (int i = (row - size < 0 ? 0 : row - size); i < (row + size >= g_rows ? g_rows - 1 : row + size); i++) {
		for (int j = (col - size < 0 ? 0 : col - size); j < (col + size >= g_cols ? g_cols - 1 : col + size); j++) {*/
	for (int i = row - size; i < row + size; i++) {
		if (i == row - size)
		{
			printf(" ");
			for (int x = 0; x < 6*size + 3; x++)
				printf("-");
			printf("\n");
		}
		for (int j = col - size; j < col + size; j++) {

			if (j == col - size) printf(" | ");

			if (i < 0 || j < 0 || i >= g_rows || j >= g_cols
				|| util_distance(i, j, g_players[0].posx, g_players[0].posy) > size) {
				printf("   ");
			}
			else if (g_field[i][j] == 'H')
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_GREEN);
				printf(" H ");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (checkformonster(i, j))					//Fix color bug (Sometimes doesnt appear for some of the monsters)
			{
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_RED);
				printf(" %c ", getmonster(i, j)->character);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (i == g_players[0].posx && j == g_players[0].posy) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_BLUE);
				printf(" %c ", PLAYERMARKER);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (g_field[i][j] == '0' || g_field[i][j] == '1' || g_field[i][j] == 'S') {
				printf("   ");
			}
			else {
				printf(" %c ", g_field[i][j]);
			}
			if (j == col + size - 1) printf("|");
		}
		if (i == row + size - 1)
		{
			printf("\n ");
			for (int x = 0; x < 6*size + 3 ; x++)
				printf("-");
			printf("\n");
		}
		printf("\n");
	}
}

void delete_field(void) {
    for (int i = 0; i < g_rows; i++) {
        free(g_field[i]);
    }

    free(g_field);
    g_field = NULL;
}

bool checkforladder(int row, int col, int count[])
{
	if (g_field[row][col] == 'H')
	{
		char temp[20] = "field";
		g_floor++;
		char level[2] = "0";
		level[0] += g_floor;
		strcat(temp, level);
		strcat(temp,".txt");
		printf("%s", temp);
		delete_field();
		read_file(temp, count);

		return true;
	}

	return false;
}
