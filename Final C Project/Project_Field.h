
#pragma once

#ifndef _PROJECT_APRATIM_MATHEUS_386711_FIELD_H_
#define _PROJECT_APRATIM_MATHEUS_386711_FIELD_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define FIELD_GROUND_CHAR '1' // can move to

char ** g_field;
int g_rows,
    g_cols;
int floor;

void read_file(const char *file_name, int count[]);

void print_field(void);
void print_viewport(void);

void delete_field(void);

// #define MAXPLAYERS 2

// typedef struct BPlayers {
//     char name[25];
//     int homeruns;
//     int hits;
// } bplayers;

// bplayers g_players[MAXPLAYERS];

// void dataInput(void);
// void dataOutput(void);
// void printPlayer(int index);
// int updateData(int index, int data[]);
// int searchPlayerName(char name[]);
// void saveToFile(void);
// void menu(void);
// int menuSelection(void);
// void selectionAction(int choice);

#endif // _PROJECT_APRATIM_MATHEUS_386711_FIELD_H_