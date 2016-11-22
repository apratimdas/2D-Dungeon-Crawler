
#pragma once

#ifndef _PROJECT_MONSTER_H_
#define _PROJECT_MONSTER_H_

#define MAXMONSTERS 1

typedef struct Monster {
    char name[25];
    int healthpoints;
    int level;
    int experience;
    int attack;
    int defence;
    int speed;
    int range;
    int posx;
    int posy;
} monster;

monster g_monsters[MAXMONSTERS];

#endif // _PROJECT_MONSTER_H_