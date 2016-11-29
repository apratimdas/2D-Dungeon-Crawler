
#include "Project_Monster.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Define other attributes like speed when needed
void init_monster()
{
	strcpy_s(g_monsters[0].name, 25, "Imp");
	g_monsters[0].attack = 10;
	g_monsters[0].healthpoints = 100;
	g_monsters[0].frequency = 4;
	g_monsters[0].character = 'I';

	strcpy_s(g_monsters[1].name, 25, "Demon");
	g_monsters[1].attack = 10;
	g_monsters[1].healthpoints = 100;
	g_monsters[1].frequency = 1;
	g_monsters[1].character = 'D';

	strcpy_s(g_monsters[2].name, 25, "Ogre");
	g_monsters[2].attack = 10;
	g_monsters[2].healthpoints = 100;
	g_monsters[2].frequency = 2;
	g_monsters[2].character = 'O';

	strcpy_s(g_monsters[3].name, 25, "Rat");
	g_monsters[3].attack = 10;
	g_monsters[3].healthpoints = 100;
	g_monsters[3].frequency = 5;
	g_monsters[3].character = 'R';

	strcpy_s(g_monsters[4].name, 25, "Thief");
	g_monsters[4].attack = 10;
	g_monsters[4].healthpoints = 100;
	g_monsters[4].frequency = 3;
	g_monsters[4].character = 'T';

}

/**
 * 
 */