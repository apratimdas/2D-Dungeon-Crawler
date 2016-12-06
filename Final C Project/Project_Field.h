
#pragma once

#ifndef _PROJECT_APRATIM_MATHEUS_386711_FIELD_H_
#define _PROJECT_APRATIM_MATHEUS_386711_FIELD_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Project_Queue.h"

#include <stdbool.h>

#define FIELD_BLOCK_CHAR '0' // cannot move to
#define FIELD_GROUND_CHAR '1' // can move to

char ** g_field;
int g_rows,
    g_cols;
int g_floor;
int g_viewport_size;

queue *g_turn_order;

void read_file(const char *file_name, int count[]);

bool checkformonster(int x, int y);
bool field_is_valid_pos(int x, int y);
void field_set_cell(int x, int y, char ch);

void print_field(void);
void print_viewport(void);

void delete_field(void);

bool checkforladder(int row, int col, int count[]);

#endif // _PROJECT_APRATIM_MATHEUS_386711_FIELD_H_