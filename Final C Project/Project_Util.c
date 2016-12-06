
#include "Project_Util.h"

#include "Project_Field.h"

//#include <time.h>
//#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//Define other attributes like speed when needed
double util_distance(int posx1, int posy1, int posx2, int posy2)
{
	return sqrt(pow(((double)posx1 - (double)posx2), 2.0) + pow(((double)posy1 - (double)posy2), 2.0));
}

bool check_valid_move(int x, int y)
{
	if (field_is_valid_pos(x, y) && !checkformonster(x, y) && g_field[x][y] == FIELD_GROUND_CHAR) return true;// && (x != g_players[0].posx && y != g_players[0].posy)) return true;
	return false;
}

void main_menu()
{
	int choice = 0;
	printf("Welcome to the game of \"Random Paradox Grinder\"\n\nChoose Diffuculty\n1) Easy\n2) Medium\n3) Hard\n");
	do
	{
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1: level_multiplier = 1;
			break;
		case 2: level_multiplier = 1.5;
			break;
		case 3: level_multiplier = 2;
			break;
		default: break;
		}
	} while (choice < 1 || choice>3);
}

void set_closest_distance(int posx1, int posy1, int posx2, int posy2, int *x, int *y)
{
	double min=INT_MAX;
	if (util_distance(posx1, posy1, posx2, posy2) < min)
	{
		min = util_distance(posx1, posy1, posx2, posy2);
		*x = posx1;
		*y = posy1;
	}
	if (util_distance(posx1, posy1 + 1, posx2, posy2) < min && check_valid_move(posx1, posy1 + 1))
	{
		min = util_distance(posx1, posy1 + 1, posx2, posy2);
		*x = posx1;
		*y = posy1 + 1;
	}
	if (util_distance(posx1, posy1 - 1, posx2, posy2) < min && check_valid_move(posx1, posy1 - 1))
	{
		min = util_distance(posx1, posy1 - 1, posx2, posy2);
		*x = posx1;
		*y = posy1 - 1;
	}	if (util_distance(posx1 + 1, posy1, posx2, posy2) < min && check_valid_move(posx1 + 1, posy1))
	{
		min = util_distance(posx1 + 1, posy1, posx2, posy2);
		*x = posx1 + 1;
		*y = posy1;
	}	if (util_distance(posx1 - 1, posy1, posx2, posy2) < min && check_valid_move(posx1 - 1, posy1))
	{
		min = util_distance(posx1 - 1, posy1, posx2, posy2);
		*x = posx1 - 1;
		*y = posy1;
	}
}

/**
*
*/