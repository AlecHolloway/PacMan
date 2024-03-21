#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>
#include "consts.h"

void movePacMan(int *pacman_ptr, int map[][columns], int direction);
int checkUpTile(int currentRow, int currentCol, int Map[][columns]);
int checkDownTile(int currentRow, int currentCol, int Map[][columns]);
int checkLeftTile(int currentRow, int currentCol, int Map[][columns]);
int checkRightTile(int currentRow, int currentCol, int Map[][columns]);

int main() {
   //consider adding AI to create new maps
   int Map[rows][columns] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 1, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1},
        {1, 3, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 3, 3, 3, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 3, 1, 1, 5, 1, 3, 1, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 3, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 1, 3, 1},
        {1, 1, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1},
        {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    bool game = true;
    initscr();
    keypad(stdscr, TRUE);
    int *pacman_ptr = &Map[10][10];
    while(game) {
        int keyboardInput = getch();
        movePacMan(pacman_ptr, Map, keyboardInput);
	    if(keyboardInput == 'q') {
            game = false;
        }
    } 
    endwin();
    return 0;
}

void movePacMan(int *pacman_ptr, int Map[][columns], int direction) { 
    int currentRow = (pacman_ptr - &Map[0][0]) / columns;
    int currentCol = (pacman_ptr - &Map[0][0]) % columns;
    
    switch(direction) {
        case KEY_UP:
            if (checkUpTile(currentRow, currentCol, Map) == Wall) { 
                printf("hitting wall\n");
            } 
            else if (checkUpTile(currentRow, currentCol, Map) == Empty) { 
                printf("Nothing\n"); 
            }
            else if (checkUpTile(currentRow, currentCol, Map) == PowerPellet) { 
                printf("PowerUP\n"); 
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Pellet) { 
                printf("Add to Score\n"); 
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Ghost) { 
                if(PowerUp == false) {
                    printf("Game Over\n"); 
                }
                else {
                }
            }
            break;
        case KEY_DOWN:
            if (checkDownTile(currentRow, currentCol, Map) == Wall) { printf("hitting wall\n"); } 
            else if (checkDownTile(currentRow, currentCol, Map) == Empty) { printf("Nothing\n"); }
            else if (checkDownTile(currentRow, currentCol, Map) == PowerPellet) { printf("PowerUP\n"); }
            else if (checkDownTile(currentRow, currentCol, Map) == Pellet) { printf("Add to Score\n"); }
            else if (checkDownTile(currentRow, currentCol, Map) == Ghost) { printf("Game Over\n"); }
            break;
        case KEY_LEFT:
            if (checkLeftTile(currentRow, currentCol, Map) == Wall) { printf("hitting wall\n"); } 
            else if (checkLeftTile(currentRow, currentCol, Map) == Empty) { printf("Nothing\n"); }
            else if (checkLeftTile(currentRow, currentCol, Map) == PowerPellet) { printf("PowerUP\n"); }
            else if (checkLeftTile(currentRow, currentCol, Map) == Pellet) { printf("Add to Score\n"); }
            else if (checkLeftTile(currentRow, currentCol, Map) == Ghost) { printf("Game Over\n"); }
            break;
        case KEY_RIGHT:
            if (checkUpTile(currentRow, currentCol, Map) == Wall) { printf("hitting wall\n"); } 
            else if (checkRightTile(currentRow, currentCol, Map) == Empty) { printf("Nothing\n"); }
            else if (checkRightTile(currentRow, currentCol, Map) == PowerPellet) { printf("PowerUP\n"); }
            else if (checkRightTile(currentRow, currentCol, Map) == Pellet) { printf("Add to Score\n"); }
            else if (checkRightTile(currentRow, currentCol, Map) == Ghost) { printf("Game Over\n"); }
            break; 
    }
}




