
#include "Project_Monster.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Define other attributes like speed when needed
void init_monster()
{
	strcpy_s(g_monsters[0].name, MONSTER_NAME_SIZE, "Imp");
	g_monsters[0].attack = 10;
	g_monsters[0].healthpoints = 100;
	g_monsters[0].frequency = 4;
	g_monsters[0].character = 'I';

	strcpy_s(g_monsters[1].name, MONSTER_NAME_SIZE, "Demon");
	g_monsters[1].attack = 10;
	g_monsters[1].healthpoints = 100;
	g_monsters[1].frequency = 1;
	g_monsters[1].character = 'D';

	strcpy_s(g_monsters[2].name, MONSTER_NAME_SIZE, "Ogre");
	g_monsters[2].attack = 10;
	g_monsters[2].healthpoints = 100;
	g_monsters[2].frequency = 2;
	g_monsters[2].character = 'O';

	strcpy_s(g_monsters[3].name, MONSTER_NAME_SIZE, "Rat");
	g_monsters[3].attack = 10;
	g_monsters[3].healthpoints = 100;
	g_monsters[3].frequency = 5;
	g_monsters[3].character = 'R';

	strcpy_s(g_monsters[4].name, MONSTER_NAME_SIZE, "Thief");
	g_monsters[4].attack = 10;
	g_monsters[4].healthpoints = 100;
	g_monsters[4].frequency = 3;
	g_monsters[4].character = 'T';

}

void copymonsterspawns(int i, int j)
{
	strcpy_s(g_spawns[i].name, MONSTER_NAME_SIZE, g_monsters[j].name);
	g_spawns[i].posx = g_monsters[j].posx;
	g_spawns[i].posy = g_monsters[j].posy;
	g_spawns[i].attack = g_monsters[j].attack;
	g_spawns[i].healthpoints = g_monsters[j].healthpoints;
	g_spawns[i].frequency = g_monsters[j].frequency;
	g_spawns[i].character = g_monsters[j].character;
}

void monster_copy_data(monster **dest, monster *orig) {
	strcpy_s((*dest)->name, MONSTER_NAME_SIZE, orig->name);
	(*dest)->character = orig->character;
	(*dest)->healthpoints = orig->healthpoints;
	(*dest)->level = orig->level;
	(*dest)->experience = orig->experience;
	(*dest)->attack = orig->attack;
	(*dest)->defence = orig->defence;
	(*dest)->speed = orig->speed;
	(*dest)->range = orig->range;
	(*dest)->posx = orig->posx;
	(*dest)->posy = orig->posy;
	(*dest)->frequency = orig->frequency;
}

monster* create_imp(void) {
	monster *mon = (monster*)malloc(sizeof(monster));
	
	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Imp");
	mon->character = 'I';
	mon->healthpoints = 15;
	mon->attack = 10;
	mon->defence = 2;
	mon->speed = 5;
	mon->frequency = 4;

	return mon;
}

monster* create_daemon(void) {
	monster *mon = (monster*)malloc(sizeof(monster));

	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Demon");
	mon->character = 'D';
	mon->healthpoints = 50;
	mon->attack = 25;
	mon->defence = 5;
	mon->speed = 4;
	mon->frequency = 1;

	return mon;
}

monster* create_ogre(void) {
	monster *mon = (monster*)malloc(sizeof(monster));

	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Ogre");
	mon->character = 'O';
	mon->healthpoints = 40;
	mon->attack = 20;
	mon->defence = 8;
	mon->speed = 1;
	mon->frequency = 2;

	return mon;
}

monster* create_rat(void) {
	monster *mon = (monster*)malloc(sizeof(monster));
	
	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Rat");
	mon->character = 'R';
	mon->healthpoints = 10;
	mon->attack = 5;
	mon->defence = 0;
	mon->speed = 3;
	mon->frequency = 5;

	return mon;
}

monster* create_thief(void) {
	monster *mon = (monster*)malloc(sizeof(monster));
	
	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Thief");
	mon->character = 'T';
	mon->healthpoints = 30;
	mon->attack = 15;
	mon->defence = 3;
	mon->speed = 5;
	mon->frequency = 3;

	return mon;
}

/**
 * 
 */