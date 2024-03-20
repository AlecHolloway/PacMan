#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>

#define rows 10
#define columns 10
#define Empty 0
#define Wall 1
#define PowerPellet 2
#define Pellet 3
#define PacMan 4
#define Ghost 5
void movePacMan(int *pacman_ptr, int map[][columns], int direction);
int checkUpTile(int currentRow, int currentCol, int Map[][columns]);
int main() {
    
    int Map[rows][columns] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,5,4,5,0,0,0},
        {0,0,0,0,0,1,0,0,0,0},
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
        case KEY_UP:
            if (checkUpTile(currentRow, currentCol, Map) == Wall) { printf("hitting wall\n"); } 
            break;
        case KEY_DOWN:
            if (currentRow > 0 && Map[currentRow + 1][currentCol] == Wall) {
                printf("Hitting wall\n");
            }
            if (currentRow > 0 && Map[currentRow + 1][currentCol] == Ghost) {
                printf("game over\n");
            }
            break;
        case KEY_LEFT:
            if (currentCol > 0 && Map[currentRow][currentCol - 1] == Wall) {
                printf("hitting wall\n");
            }
            if (currentCol > 0 && Map[currentRow][currentCol - 1] == Ghost) {
                printf("game over\n");
            }
            break;
        case KEY_RIGHT:
            if (currentCol > 0 && Map[currentRow][currentCol + 1] == Wall) {
                printf("hitting wall\n");
            }
            if (currentCol > 0 && Map[currentRow][currentCol + 1] == 4) {
                printf("game over\n");
            }
            break;
    }
}

int checkUpTile(int currentRow, int currentCol, int Map[][columns]) {
    if (currentRow > 0 && Map[currentRow - 1][currentCol] == Wall) { return Wall; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == Ghost) { return Ghost; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == Empty) { return Empty; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == Pellet) { return Pellet; }
}
int checkDownTile();
int checkLeftTile();
int checkTile();
