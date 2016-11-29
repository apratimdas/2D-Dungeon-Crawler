
#pragma once

#ifndef _PROJECT_MONSTER_H_
#define _PROJECT_MONSTER_H_

#define MAXMONSTERS 5

typedef struct Monster {
    char name[25];
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

monster g_monsters[MAXMONSTERS];

#endif // _PROJECT_MONSTER_H_