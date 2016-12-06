
#pragma once

#ifndef _PROJECT_PLAYER_H_
#define _PROJECT_PLAYER_H_

#define MAXPLAYERS 1
#define PLAYERMARKER 'Y'

typedef struct Player {
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
} player;

player g_players[MAXPLAYERS];

#endif // _PROJECT_PLAYER_H_