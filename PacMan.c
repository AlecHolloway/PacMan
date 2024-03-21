#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>
#include "consts.h"
#include <pthread.h>

struct Stats {
    int score;
    bool powerUp;
};

void movePacMan(int *pacman_ptr, int map[][columns], int direction, struct Stats *);
int checkUpTile(int currentRow, int currentCol, int Map[][columns]);
int checkDownTile(int currentRow, int currentCol, int Map[][columns]);
int checkLeftTile(int currentRow, int currentCol, int Map[][columns]);
int checkRightTile(int currentRow, int currentCol, int Map[][columns]);
void *handlePowerUp(void *);

int main() {

    int Map[rows][columns] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 1, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1},
        {1, 3, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 3, 3, 3, 1},
        {1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 3, 3, 3, 1, 2, 4, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 3, 1, 1, 5, 2, 3, 1, 3, 3, 3, 3, 3, 3, 1},
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
    struct Stats *playerStats = (struct Stats*)malloc(sizeof(struct Stats));
    initscr();
    keypad(stdscr, TRUE);
    int *pacman_ptr = &Map[9][9];
    playerStats->powerUp = false;
    playerStats->score = 0;
    while(game) {
        int keyboardInput = getch();
        movePacMan(pacman_ptr, Map, keyboardInput, playerStats);
            if(keyboardInput == 'q') {
            game = false;
        }
    }
    endwin();
    return 0;
}

void movePacMan(int *pacman_ptr, int Map[][columns], int direction, struct Stats *playerStats) {
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
                if(playerStats->powerUp == true) {

                }
                else {
                    playerStats->powerUp = false;
               //create thread to run this with a timer to end.
                    pthread_t tid;
                    if(pthread_create(&tid, NULL, handlePowerUp, (void*)playerStats)) {
                        fprintf(stderr, "error creating thread\n");
                    }
                }
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Pellet) {
                printf("Add to Score\n");
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Ghost) {
                if(playerStats->powerUp == false) {
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



void *handlePowerUp(void *playerStats) {
        struct Stats *pStats = (struct Stats *)playerStats;
        int seconds = 10;
        printf("power up enabled\n");
        sleep(10);
        pStats->powerUp = false;
        printf("power up disabled\n");
        pthread_exit(NULL);
}



