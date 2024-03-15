#include<stdio.h>
#include<stdlib.h>
#include<SDL2.h/SDL.h>
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
}

int movePacMan(int map[rows][columns]) {

}
