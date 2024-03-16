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
        int input;
        int *pacman_ptr = &Map[4,5];
	input = getch();
        //printf("%d", input);
        movePacMan(pacman_ptr, Map, input);
	if(game == false) {
            return 1;
        }

    } 
}

void movePacMan(int *pacman_ptr,int map[rows][columns], int direction) {
    switch(direction) {
	case KEY_UP:
	    printf("Hello World");
    }
}
int checkNextMapValue(int map[rows][columns], int direction) {

}
