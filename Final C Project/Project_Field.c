
#include "Project_Field.h"
#include "Project_Player.h" // for starting position
#include "Project_Monster.h" // for initial monster spawns
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include<Windows.h>


#define VIEWPORT_SIZE 5

/**
 * Test
 */

void monsterspawner();
void resetmonsters();

void read_file(const char *file_name, int count[]) {
    FILE *myfile;
    int rows = 0; 
    int cols = 0; 
    char ch;

    if((myfile = fopen(file_name, "r")) == NULL) {
        printf("Cannot open file.\n");
		getchar();
        exit(1);
    }

    while(!feof(myfile)) {
        ch = fgetc(myfile);
        if(ch == '\n') {
            rows++;
        } else if (rows == 0) {
            cols++;
        }
    }

    rewind(myfile);

    count[0] = g_rows = rows;
    count[1] = g_cols = cols;

    g_field = (char**)malloc(sizeof(char*) * g_rows);

    for (int i = 0; i < g_rows; i++) {
        g_field[i] = (char*)malloc(sizeof(char) * g_cols);
    }

    for (int i = 0; i < g_rows; i++) {
        for (int j = 0; j < g_cols; j++) {
            g_field[i][j] = '0';
        }
    }

    rows = 0;
    cols = 0;

    while(!feof(myfile)) {
        ch = fgetc(myfile);

        if(ch == '\n') {
            cols = 0;
            rows++;
        } else if (rows < g_rows) {
			if (ch == 'S') {
				g_field[rows][cols] = FIELD_GROUND_CHAR;

				for (int i = 0; i < MAXPLAYERS; i++) {
					g_players[i].posx = rows; // maybe create set functions
					g_players[i].posy = cols;
					//printf("%d, %d, %d\n", rows, cols, g_players[i].posx);
				}
			}
			else {
				g_field[rows][cols] = ch;
			}
            cols++;
        }
    }
	resetmonsters();
	monsterspawner();
}

void resetmonsters()
{
	for (int i = 0; i < MAXMONSTERS; i++)
	{
		g_monsters[i].posx = -1;
		g_monsters[i].posy = -1;
	}
}

//Need to modify spawn location here
void monsterspawner()
{
	int i, j, r, ctr = 0;
	srand(time(0));
	do
	{
		i = rand() % g_rows;
		j = rand() % g_cols;
		if (g_field[i][j] != '1');
		else
		{
			r = rand();
			if ((r % 15) >= 0 && (r % 15) <= 4)
			{
				//set monster with freq 5
				g_monsters[3].posx = i;
				g_monsters[3].posy = j;
				//g_field[i][j] = g_monsters[3].character;
				copymonsterspawns(ctr, 3);
				printf("Monster 1\n");
			}
			else if ((r % 15) >= 5 && (r % 15) <= 8)
			{
				//freq 4
				g_monsters[0].posx = i;
				g_monsters[0].posy = j;
				//g_field[i][j] = g_monsters[0].character;
				copymonsterspawns(ctr, 0);
				printf("Monster 2\n");
			}
			else if ((r % 15) >= 9 && (r % 15) <= 11)
			{
				g_monsters[4].posx = i;
				g_monsters[4].posy = j;
				//g_field[i][j] = g_monsters[4].character;
				copymonsterspawns(ctr, 4);
				printf("Monster 3\n");
			}
			else if ((r % 15) >= 12 && (r % 15) <= 13)
			{
				g_monsters[2].posx = i;
				g_monsters[2].posy = j;
				//g_field[i][j] = g_monsters[2].character;
				copymonsterspawns(ctr, 2);
				printf("Monster 4\n");
			}
			else
			{
				g_monsters[1].posx = i;
				g_monsters[1].posy = j;
				//g_field[i][j] = g_monsters[1].character;
				copymonsterspawns(ctr, 1);
				printf("Monster 5\n");
			}
			ctr++;
		}

	} while (ctr < 5);
}

bool checkformonster(int x, int y)
{
	for (int i = 0; i < MAXMONSTERS; i++) if (x == g_spawns[i].posx && y == g_spawns[i].posy) return true;
	return false;
}

int getmonsterindex(int x, int y)
{
	for (int i = 0; i < MAXMONSTERS; i++) if (x == g_spawns[i].posx && y == g_spawns[i].posy) return i;
	return -1;
}

/*
void print_field(void) {
    for (int i = 0; i < g_rows; i++) {
        for (int j = 0; j < g_cols; j++) {
			if (checkformonster(i, j))
			{
				//add color
				//SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_RED);
				//printf("%c", g_field[i][j]);
				//SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (i == g_players[0].posx && j == g_players[0].posy) {
				printf("%c", PLAYERMARKER);
			}
            else if (g_field[i][j] == '0' || g_field[i][j] == '1' || g_field[i][j] == 'S') {
                printf(" ");
            }
            else {
				//SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_RED);
                //printf("%c", g_field[i][j]);
            }
        }

        printf("\n");
    }
}
*/

void print_viewport(void) {

	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	int size = VIEWPORT_SIZE,
		row = g_players[0].posx,
		col = g_players[0].posy;

	/*for (int i = (row - size < 0 ? 0 : row - size); i < (row + size >= g_rows ? g_rows - 1 : row + size); i++) {
		for (int j = (col - size < 0 ? 0 : col - size); j < (col + size >= g_cols ? g_cols - 1 : col + size); j++) {*/
	for (int i = row - size; i < row + size; i++) {
		if (i == row - size)
		{
			printf(" ");
			for (int x = 0; x < 6*size + 3; x++)
				printf("-");
			printf("\n");
		}
		for (int j = col - size; j < col + size; j++) {

			if (j == col-size) printf(" | ");

			if (i < 0 || j < 0 || i >= g_rows || j >= g_cols) {
				printf("   ");
			}
			else if (g_field[i][j] == 'H')
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_GREEN);
				printf(" H ");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (checkformonster(i, j))					//Fix color bug (Sometimes doesnt appear for some of the monsters)
			{
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_RED);
				printf(" %c ", g_spawns[getmonsterindex(i, j)].character);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (i == g_players[0].posx && j == g_players[0].posy) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | BACKGROUND_BLUE);
				printf(" %c ", PLAYERMARKER);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			}
			else if (g_field[i][j] == '0' || g_field[i][j] == '1' || g_field[i][j] == 'S') {
				printf("   ");
			}
			else {
				printf(" %c ", g_field[i][j]);
			}
			if (j == col + size - 1) printf("|");
		}
		if (i == row + size - 1)
		{
			printf("\n ");
			for (int x = 0; x < 6*size + 3 ; x++)
				printf("-");
			printf("\n");
		}
		printf("\n");
	}
}

void delete_field(void) {
    for (int i = 0; i < g_rows; i++) {
        free(g_field[i]);
    }

    free(g_field);
    g_field = NULL;
}

void checkforladder(int row, int col, int count[])
{
	if (g_field[row][col] == 'H')
	{
		char temp[20] = "field";
		floor++;
		char level[2] = "0";
		level[0] += floor;
		strcat(temp, level);
		strcat(temp,".txt");
		printf("%s", temp);
		delete_field();
		read_file(temp, count);
	}
}

// void dataInput(void) {
//     for (int i = 0; i < MAXPLAYERS; i++) {
//         printf("Please, enter player #%d of %d name, number of home runs and number of hits:\n", i + 1, MAXPLAYERS);
//         scanf("%s", g_players[i].name);
//         scanf("%d", &g_players[i].homeruns);
//         scanf("%d", &g_players[i].hits);
//     }
// }

// void dataOutput(void) {
//     // print data in a tabular form
//     printf("Player Name\t\t# Home Runs\t# Hits\n");

//     for (int i = 0; i < MAXPLAYERS; i++) {
//         printf("%-10s\t\t%d\t\t%d\n", g_players[i].name, g_players[i].homeruns, g_players[i].hits);
//     }
// }

// void printPlayer(int index) {
//     // print data of a specific player
//     printf("Player Name: %s\n", g_players[index].name);
//     printf("# of Home Runs: %d\n", g_players[index].homeruns);
//     printf("# of Hits: %d\n", g_players[index].hits);
// }

// int updateData(int index, int data[]) {
//     if (data[0] < 0) {
//         data[0] *= -1;
//         g_players[index].homeruns += data[0];
//     }
//     else {
//         g_players[index].homeruns = data[0];
//     }

//     if (data[1] < 0) {
//         data[1] *= -1;
//         g_players[index].hits += data[1];
//     }
//     else {
//         g_players[index].hits = data[1];
//     }

//     return 0;
// }

// int searchPlayerName(char name[]) {
//     // searches the array for the information given
//     for (int i = 0; i < MAXPLAYERS; i++) {
//         if (strcmp(name, g_players[i].name) == 0) {
//             return i;
//         }
//     }

//     return -1;
// }

// void saveToFile(void) {
//     FILE *f = fopen("output.txt", "wb+");
//     if (f == NULL)
//     {
//         printf("Error opening file...\n");
//         exit(1);
//     }

//     // print data in a tabular form
//     fprintf(f, "Player Name\t\t# Home Runs\t# Hits\n");

//     for (int i = 0; i < MAXPLAYERS; i++) {
//         fprintf(f, "%-10s\t\t%d\t\t%d\n", g_players[i].name, g_players[i].homeruns, g_players[i].hits);
//     }

//     fclose(f);

//     printf("File saved successfully!\n");
// }

// void menu(void) {
//     printf("Please, select one of the following options:\n");
//     printf("1 - Print players' data;\n");
//     printf("2 - Search player's data by name;\n");
//     printf("3 - Update player's data;\n");
//     printf("4 - Save data to a file;\n");
//     printf("5 - Exit program.\n");
// }

// int menuSelection(void) {
//     int choice = -1;

//     do {
//         menu();
//         scanf("%d", &choice);
//     } while (choice < 1 || choice > 5);

//     return choice;
// }

// void selectionAction(int choice) {
//     switch (choice) {
//     case 1:
//         dataOutput();
//         break;
//     case 2:
//     {
//         char name[25];
//         int index;

//         printf("Enter the player's name to search:\n");
//         scanf("%s", name);

//         index = searchPlayerName(name);

//         if (index == -1) {
//             printf("Player not found!\n");
//         }
//         else {
//             printf("Player found at position %d.\n", index);
//             printPlayer(index);
//         }

//         getchar();
//         break;
//         // scanf("%s", name, 24);
//     }
//     case 3:
//     {
//         char name[25];
//         int index,
//             data[2];

//         printf("Enter the name of the player whose data you wish to update:\n");
//         scanf("%s", name);

//         index = searchPlayerName(name);

//         if (index == -1) {
//             printf("Player not found, try again.\n");
//         }
//         else {
//             printf("Player found at position %d.\n", index);
//             printPlayer(index);

//             printf("Enter the new number of homeruns and hits you wish to give the player\n");
//             printf("(enter a negative number to add to the current value):\n");
//             scanf("%d", &data[0]);
//             scanf("%d", &data[1]);

//             updateData(index, data);
//             printPlayer(index);
//         }

//         getchar();
//         break;
//     }
//     case 4:
//     {
//         saveToFile();
//     }
//     default:
//         break;
//     }
// }