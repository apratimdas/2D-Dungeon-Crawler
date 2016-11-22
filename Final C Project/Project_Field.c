
#include "Project_Field.h"
#include "Project_Player.h" // for starting position

#include <time.h>
#include <string.h>

#define VIEWPORT_SIZE 5

/**
 * 
 */

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
					printf("%d, %d, %d\n", rows, cols, g_players[i].posx);
				}
			}
			else {
				g_field[rows][cols] = ch;
			}
            cols++;
        }
    }
}

void print_field(void) {
    for (int i = 0; i < g_rows; i++) {
        for (int j = 0; j < g_cols; j++) {
			if (i == g_players[0].posx && j == g_players[0].posy) {
				printf("%c", PLAYERMARKER);
			}
            else if (g_field[i][j] == '0' || g_field[i][j] == '1' || g_field[i][j] == 'S') {
                printf(" ");
            }
            else {
                printf("%c", g_field[i][j]);
            }
        }

        printf("\n");
    }
}

void print_viewport(void) {
	int size = VIEWPORT_SIZE,
		row = g_players[0].posx,
		col = g_players[0].posy;

	/*for (int i = (row - size < 0 ? 0 : row - size); i < (row + size >= g_rows ? g_rows - 1 : row + size); i++) {
		for (int j = (col - size < 0 ? 0 : col - size); j < (col + size >= g_cols ? g_cols - 1 : col + size); j++) {*/
	for (int i = row - size; i < row + size; i++) {
		for (int j = col - size; j < col + size; j++) {
			if (i < 0 || j < 0 || i >= g_rows || j >= g_cols) {
				printf(" ");
			}
			else if (i == g_players[0].posx && j == g_players[0].posy) {
				printf("%c", PLAYERMARKER);
			}
			else if (g_field[i][j] == '0' || g_field[i][j] == '1' || g_field[i][j] == 'S') {
				printf(" ");
			}
			else {
				printf("%c", g_field[i][j]);
			}
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