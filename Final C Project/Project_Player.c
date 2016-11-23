
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Project_Player.h"

void init()
{
	for (int i = 0; i < MAXPLAYERS; i++)
	{
		//Can implement a character creation option:
		//printf("Enter Name of you Character: ");
		//scanf("%s", g_players[i].name, 25);
		strcpy_s(g_players[i].name, 25, "Bob");
		g_players[i].attack = 10;
		g_players[i].healthpoints = 100;

	}
}

/**
 * 
 */

