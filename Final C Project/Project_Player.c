
#include "Project_Player.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_player()
{
	for (int i = 0; i < MAXPLAYERS; i++)
	{
		//Can implement a character creation option:
		//printf("Enter Name of you Character: ");
		//scanf("%s", g_players[i].name, 25);
		strcpy_s(g_players[i].name, 25, "Bob");
		g_players[i].level = 1;
		g_players[i].experience = 0;
		g_players[i].healthpoints = 500;
		g_players[i].attack = 100;
		g_players[i].defence = 5;
		g_players[i].speed = 3;
	}
}

/**
 * 
 */

