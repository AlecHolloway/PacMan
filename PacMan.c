#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>

#define rows 10
#define columns 10

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
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };
    bool game = true; 
    while(game) {
        //get keyboard input
        char input;
        scanf("%c", &input);

        if(game == false) {
            return 1;
        }

    } 
}

int movePacMan(int map[rows][columns]) {
}
