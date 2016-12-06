
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

monster* create_imp(double level) {
	monster *mon = (monster*)malloc(sizeof(monster));
	
	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Imp");
	mon->character = 'I';
	mon->level =			(int)level;
	mon->experience =		(int)level;
	mon->healthpoints =		(int)(15 * level);
	mon->attack =			(int)(10 * level);
	mon->defence =			(int)(2 * level);
	mon->speed =			5;
	mon->frequency =		4;

	return mon;
}

monster* create_daemon(double level) {
	monster *mon = (monster*)malloc(sizeof(monster));

	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Demon");
	mon->character = 'D';
	mon->level =			(int)level;
	mon->experience =		(int)level;
	mon->healthpoints =		(int)(50 * level);
	mon->attack =			(int)(25 * level);
	mon->defence =			(int)(5 * level);
	mon->speed =			4;
	mon->frequency =		1;

	return mon;
}

monster* create_ogre(double level) {
	monster *mon = (monster*)malloc(sizeof(monster));

	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Ogre");
	mon->character = 'O';
	mon->level =			(int)level;
	mon->experience =		(int)level;
	mon->healthpoints =		(int)(40 * level);
	mon->attack =			(int)(20 * level);
	mon->defence =			(int)(5 * level);
	mon->speed =			1;
	mon->frequency =		2;

	return mon;
}

monster* create_rat(double level) {
	monster *mon = (monster*)malloc(sizeof(monster));
	
	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Rat");
	mon->character = 'R';
	mon->level =			(int)level;
	mon->experience =		(int)level;
	mon->healthpoints =		(int)(10 * level);
	mon->attack =			(int)(5 * level);
	mon->defence =			(int)(0 * level);
	mon->speed =			3;
	mon->frequency =		5;

	return mon;
}

monster* create_thief(double level) {
	monster *mon = (monster*)malloc(sizeof(monster));
	
	strcpy_s(mon->name, MONSTER_NAME_SIZE, "Thief");
	mon->character = 'T';
	mon->level =			(int)level;
	mon->experience =		(int)level;
	mon->healthpoints =		(int)(30 * level);
	mon->attack =			(int)(15 * level);
	mon->defence =			(int)(3 * level);
	mon->speed =			5;
	mon->frequency =		3;

	return mon;
}

/**
 * 
 */