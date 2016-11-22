
#pragma once

#ifndef _PROJECT_PLAYER_H_
#define _PROJECT_PLAYER_H_

// char ** g_field;
// int g_rows,
//     g_cols;

// void read_file(const char *file_name, int count[]);

// void print_field(void);

// void delete_field(void);

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