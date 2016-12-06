
#pragma once

#ifndef _PROJECT_MONSTER_H_
#define _PROJECT_MONSTER_H_

#define MAXMONSTERS 5
#define MONSTERVARIETY 5
#define MONSTER_NAME_SIZE 25

typedef struct Monster {
    char name[MONSTER_NAME_SIZE];
	char character;
    int healthpoints;
    int level;
    int experience;
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

void monster_copy_data(monster **dest, monster *orig);

#endif // _PROJECT_MONSTER_H_