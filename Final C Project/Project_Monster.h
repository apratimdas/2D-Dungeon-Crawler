
#pragma once

#ifndef _PROJECT_MONSTER_H_
#define _PROJECT_MONSTER_H_

#define MAXMONSTERS 5
#define MONSTERVARIETY 5
#define MONSTER_NAME_SIZE 25

typedef struct Monster {
    char name[MONSTER_NAME_SIZE];
	char character;
	double level;
	int experience;
    int healthpoints;
    int attack;
    int defence;
    int speed;
    int range;
    int posx;
    int posy;
	int frequency;
} monster;

monster g_monsters[MONSTERVARIETY];
monster g_spawns[MAXMONSTERS];

void init_monster();

void monster_copy_data(monster **dest, monster *orig);

monster* create_imp(double level);
monster* create_daemon(double level);
monster* create_ogre(double level);
monster* create_rat(double level);
monster* create_thief(double level);

#endif // _PROJECT_MONSTER_H_