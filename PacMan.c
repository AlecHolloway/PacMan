#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>

#define rows 10
#define columns 10

void movePacMan(int *pacman_ptr, int map[rows][columns], int direction);
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
    while(game) {
        //get keyboard input
        int input = getch();
        int *pacman_ptr = &Map[4][5];
        movePacMan(pacman_ptr, Map, input);
	    if(input == 'q') {
            game = false;
        }
    } 
    endwin();
    return 0;
}

void movePacMan(int *pacman_ptr,int map[rows][columns], int direction) {
    switch(direction) {
        case KEY_UP:
            printf("keyup\n");
        case KEY_DOWN:
            printf("keydown\n");
        case KEY_LEFT:
            printf("KEYleft\n");
        case KEY_RIGHT:
            printf("KEYRIGHT\n");    
    }
}
