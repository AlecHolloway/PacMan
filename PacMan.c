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
int checkDownTile(int currentRow, int currentCol, int Map[][columns]);
int checkLeftTile(int currentRow, int currentCol, int Map[][columns]);
int checkRightTile(int currentRow, int currentCol, int Map[][columns]);



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
            else if (checkUpTile(currentRow, currentCol, Map) == Empty) { printf("Nothing\n"); }
            else if (checkUpTile(currentRow, currentCol, Map) == PowerPellet) { printf("PowerUP\n"); }
            else if (checkUpTile(currentRow, currentCol, Map) == Pellet) { printf("Add to Score\n"); }
            else if (checkUpTile(currentRow, currentCol, Map) == Ghost) { printf("Game Over\n"); }
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

//move these to a sepearate .h file
int checkUpTile(int currentRow, int currentCol, int Map[][columns]) {
    if (currentRow > 0 && Map[currentRow - 1][currentCol] == Wall) { return Wall; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == Ghost) { return Ghost; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == Empty) { return Empty; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && Map[currentRow - 1][currentCol] == Pellet) { return Pellet; }
}
int checkDownTile(int currentRow, int currentCol, int Map[][columns]) {
    if (currentRow > 0 && Map[currentRow + 1][currentCol] == Wall) { return Wall; }
    else if (currentRow > 0 && Map[currentRow + 1][currentCol] == Ghost) { return Ghost; }
    else if (currentRow > 0 && Map[currentRow + 1][currentCol] == Empty) { return Empty; }
    else if (currentRow > 0 && Map[currentRow + 1][currentCol] == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && Map[currentRow + 1][currentCol] == Pellet) { return Pellet; }
}
int checkLeftTile(int currentRow, int currentCol, int Map[][columns]) {
    if (currentRow > 0 && Map[currentRow ][currentCol - 1] == Wall) { return Wall; }
    else if (currentRow > 0 && Map[currentRow][currentCol - 1] == Ghost) { return Ghost; }
    else if (currentRow > 0 && Map[currentRow][currentCol - 1] == Empty) { return Empty; }
    else if (currentRow > 0 && Map[currentRow][currentCol - 1] == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && Map[currentRow][currentCol - 1] == Pellet) { return Pellet; }
}
int checkRightTile(int currentRow, int currentCol, int Map[][columns]) {
    if (currentRow > 0 && Map[currentRow][currentCol + 1] == Wall) { return Wall; }
    else if (currentRow > 0 && Map[currentRow][currentCol + 1] == Ghost) { return Ghost; }
    else if (currentRow > 0 && Map[currentRow][currentCol + 1] == Empty) { return Empty; }
    else if (currentRow > 0 && Map[currentRow][currentCol + 1] == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && Map[currentRow][currentCol + 1] == Pellet) { return Pellet; }
}
;
