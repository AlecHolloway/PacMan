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
        //get keyboard input
        int input = getch();
        movePacMan(pacman_ptr, Map, input);
	    if(input == 'q') {
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
            if (currentRow > 0 && Map[currentRow - 1][currentCol] != 0) {
                pacman_ptr -= columns; // Move up by adjusting pointer
            }
            break;
        case KEY_DOWN:
            printf("keydown\n");
            break;
        case KEY_LEFT:
            printf("KEYleft\n");
            break;
        case KEY_RIGHT:
            printf("KEYRIGHT\n");    
            break;
    }
}
