#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>

#define rows 10
#define columns 10

void movePacMan(int *pacman_ptr, int map[][columns], int direction);
int main() {
    int wall = 0;
    int pellet = 1;
    int powerPellet = 2;
    int pacman = 3;
    int ghost = 4;

    int Map[rows][columns] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,3,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };
    bool game = true;
    initscr();
    keypad(stdscr, TRUE);
    int *pacman_ptr = &Map[4][5];
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
        //int KeyUpNextTile = checkKeyUpNextTile();
        case KEY_UP:
          //if (KeyUpNextTile == 0) { printf("hitting wall"); }
            if (currentRow > 0 && Map[currentRow - 1][currentCol] == 0) {
                printf("hitting wall\n");
            }
            if (currentRow > 0 && Map[currentRow - 1][currentCol] == 4) {
               printf("game over\n");
            } 
            break;
        case KEY_DOWN:
            if (currentRow > 0 && Map[currentRow + 1][currentCol] == 0) {
                printf("Hitting wall\n");
            }
            if (currentRow > 0 && Map[currentRow + 1][currentCol] == 4) {
                printf("game over\n");
            }
            break;
        case KEY_LEFT:
            if (currentCol > 0 && Map[currentRow][currentCol - 1] == 0) {
                printf("hitting wall\n");
            }
            if (currentCol > 0 && Map[currentRow][currentCol - 1] == 4) {
                printf("game over\n");
            }
            break;
        case KEY_RIGHT:
            if (currentCol > 0 && Map[currentRow][currentCol + 1] == 0) {
                printf("hitting wall\n");
            }
            if (currentCol > 0 && Map[currentRow][currentCol + 1] == 4) {
                printf("game over\n");
            }
            break;
    }
}

int checkKeyUpNextTile();
int checkKeyDownNextTile();
int checkKeyLeftNextTile();
int checkKeyRightNextTile();
