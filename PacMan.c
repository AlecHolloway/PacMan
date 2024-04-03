#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>
#include "consts.h"
#include <pthread.h>

struct Stats {
    int score;
    bool powerUp;
    int lifes;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int *movePacMan(int *pacman_ptr, void *map, int direction, struct Stats *);
int checkUpTile(int currentRow, int currentCol, void *map_ptr);
int checkDownTile(int currentRow, int currentCol, void *map_ptr);
int checkLeftTile(int currentRow, int currentCol, void *map_ptr);
int checkRightTile(int currentRow, int currentCol, void *map_ptr);
void *handlePowerUp(void *);
void printMap(void *map_ptr);
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
        {1, 1, 1, 1, 3, 3, 3, 1, 2, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 3, 10, 3, 4, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1},
        {1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1},
        {1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1},
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
    playerStats->lifes = 3;

    while(game) {
        printMap(Map);
        int keyboardInput = getch();
        //movePacMan function should return new pacman pointer
        pacman_ptr = movePacMan(pacman_ptr, Map, keyboardInput, playerStats);
        if(keyboardInput == 'q') {
            game = false;
        }
    }
    endwin();
    return 0;
}
//return address of PacMan
int *movePacMan(int *pacman_ptr, void *Map, int direction, struct Stats *playerStats) {
    int(*mapPtr)[columns] = Map;
    int currentRow = (pacman_ptr - *mapPtr) / columns;
    int currentCol = (pacman_ptr - *mapPtr) % columns;

    switch(direction) {
        case KEY_UP:
            if (checkUpTile(currentRow, currentCol, Map) == Wall) {
                printw("hitting wall\n");
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Empty) {
                printw("empty\n");
                mapPtr[currentRow - 1][currentCol] = 4;
                pacman_ptr = &mapPtr[currentRow - 1][currentCol];
                mapPtr[currentRow][currentCol] = 0;
                return pacman_ptr;
            }
            else if (checkUpTile(currentRow, currentCol, Map) == PowerPellet) {
                pthread_t tid;
                //if thread is in execution stop execution and start a fresh one
                //essentially setting the timer back to 10
                //
                //is there a tid value that indicates it is not executing
                if(playerStats->powerUp == true) {
                    //handlePowerUp();
                    mapPtr[currentRow][currentCol] = Empty;
                    pacman_ptr = &mapPtr[currentRow - 1][currentCol];
                    return pacman_ptr; 
                }
                else {
                    playerStats->powerUp = false;
                    if(pthread_create(&tid, NULL, handlePowerUp, (void*)playerStats)) {
                        fprintf(stderr, "error creating thread\n");
                    }
                    return pacman_ptr;
                }
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Pellet) {
                mapPtr[currentRow][currentCol] = Empty;
                playerStats->score += 10;
                printw("slot is now empty\n");
                mapPtr[currentRow - 1][currentCol] = 4;
                pacman_ptr = &mapPtr[currentRow - 1][currentCol];
                return pacman_ptr; 
            }
            else if (checkUpTile(currentRow, currentCol, Map) == Ghost) {
                if(playerStats->powerUp == false) {
                    printw("Game Over\n");
                }
                else {
                    //TODO:reset ghost by going to block that contains 6
                    //or wait 5-10 seconds before ghost is back to normal
                }
            }
            break;
        case KEY_DOWN:
            if (checkDownTile(currentRow, currentCol, Map) == Wall) {
                printw("hitting wall\n");
            }
            else if (checkDownTile(currentRow, currentCol, Map) == Empty) {
                printw("empty\n");
                mapPtr[currentRow + 1][currentCol] = 4;
                mapPtr[currentRow][currentCol] = 0;
                pacman_ptr = &mapPtr[currentRow + 1][currentCol];
                return pacman_ptr;
            }
            else if (checkDownTile(currentRow, currentCol, Map) == PowerPellet) {
                pthread_t tid;
                //if thread is in execution stop execution and start a fresh one
                //essentially setting the timer back to 10
                //
                //is there a tid value that indicates it is not executing
                if(playerStats->powerUp == true) {
                    //handlePowerUp();
                    mapPtr[currentRow][currentCol] = Empty;
                    pacman_ptr = &mapPtr[currentRow + 1][currentCol];
                    return pacman_ptr; 
                }
                else {
                    playerStats->powerUp = false;
                    if(pthread_create(&tid, NULL, handlePowerUp, (void*)playerStats)) {
                        fprintf(stderr, "error creating thread\n");
                    }
                    return pacman_ptr;
                }
            }
            else if (checkDownTile(currentRow, currentCol, Map) == Pellet) {
                mapPtr[currentRow][currentCol] = Empty;
                playerStats->score += 10;
                printw("slot is now empty\n");
                mapPtr[currentRow + 1][currentCol] = 4;
                pacman_ptr = &mapPtr[currentRow + 1][currentCol];
                return pacman_ptr; 
            }
            else if (checkDownTile(currentRow, currentCol, Map) == Ghost) {
                if(playerStats->powerUp == false) {
                    printw("Game Over\n");
                }
                else {
                    //TODO:reset ghost by going to block that contains 6
                    //or wait 5-10 seconds before ghost is back to normal
                }
            }
            break;
        case KEY_LEFT:
            if (checkLeftTile(currentRow, currentCol, Map) == Wall) {
                printw("hitting wall\n");
            }
            else if (checkLeftTile(currentRow, currentCol, Map) == Empty) {
                printw("empty\n");
                mapPtr[currentRow][currentCol - 1] = 4;
                pacman_ptr = &mapPtr[currentRow][currentCol - 1];
                mapPtr[currentRow][currentCol] = 0;
                return pacman_ptr;
            }
            else if (checkLeftTile(currentRow, currentCol, Map) == PowerPellet) {
                pthread_t tid;
                //if thread is in execution stop execution and start a fresh one
                //essentially setting the timer back to 10
                //
                //is there a tid value that indicates it is not executing
                if(playerStats->powerUp == true) {
                    //handlePowerUp();
                    mapPtr[currentRow][currentCol] = Empty;
                    pacman_ptr = &mapPtr[currentRow][currentCol - 1];
                    return pacman_ptr; 
                }
                else {
                    playerStats->powerUp = false;
                    if(pthread_create(&tid, NULL, handlePowerUp, (void*)playerStats)) {
                        fprintf(stderr, "error creating thread\n");
                    }
                    return pacman_ptr;
                }
            }
            else if (checkLeftTile(currentRow, currentCol, Map) == Pellet) {
                mapPtr[currentRow][currentCol] = Empty;
                playerStats->score += 10;
                printw("slot is now empty\n");
                mapPtr[currentRow][currentCol - 1] = 4;
                pacman_ptr = &mapPtr[currentRow][currentCol - 1];
                return pacman_ptr; 
            }
            else if (checkLeftTile(currentRow, currentCol, Map) == Ghost) {
                if(playerStats->powerUp == false) {
                    printw("Game Over\n");
                    exit(1);
                }
                else {
                    //TODO:reset ghost by going to block that contains 6
                    //or wait 5-10 seconds before ghost is back to normal
                }
            }
            break;
        case KEY_RIGHT:
            if (checkRightTile(currentRow, currentCol, Map) == Wall) {
                printw("hitting wall\n");
            }
            else if (checkRightTile(currentRow, currentCol, Map) == Empty) {
                printw("empty\n");
                mapPtr[currentRow][currentCol + 1] = 4;
                pacman_ptr = &mapPtr[currentRow][currentCol + 1];
                mapPtr[currentRow][currentCol] = 0;
                return pacman_ptr;
            }
            else if (checkRightTile(currentRow, currentCol, Map) == PowerPellet) {
                pthread_t tid;
                //if thread is in execution stop execution and start a fresh one
                //essentially setting the timer back to 10
                //
                //is there a tid value that indicates it is not executing
                if(playerStats->powerUp == true) {
                    //handlePowerUp();
                    mapPtr[currentRow][currentCol] = Empty;
                    pacman_ptr = &mapPtr[currentRow][currentCol + 1];
                    return pacman_ptr; 
                }
                else {
                    playerStats->powerUp = false;
                    if(pthread_create(&tid, NULL, handlePowerUp, (void*)playerStats)) {
                        fprintf(stderr, "error creating thread\n");
                    }
                    return pacman_ptr;
                }
            }
            else if (checkRightTile(currentRow, currentCol, Map) == Pellet) {
                mapPtr[currentRow][currentCol] = Empty;
                playerStats->score += 10;
                printw("slot is now empty\n");
                mapPtr[currentRow][currentCol + 1] = 4;
                pacman_ptr = &mapPtr[currentRow][currentCol + 1];
                return pacman_ptr; 
            }
            else if (checkRightTile(currentRow, currentCol, Map) == Ghost) {
                if(playerStats->powerUp == false) {
                    printw("Game Over\n");
                }
                else {
                    //TODO:reset ghost by going to block that contains 6
                    //or wait 5-10 seconds before ghost is back to normal
                }
            }
            break;
    }
}



void *handlePowerUp(void *playerStats) {
        struct Stats *pStats = (struct Stats *)playerStats;
        printf("power up enabled\n");
        sleep(10);
        pthread_mutex_lock(&mutex);
        pStats->powerUp = false;
        pthread_mutex_unlock(&mutex);
        printf("power up disabled\n");
        pthread_exit(NULL);
}

//TODO
void moveInky();
void movePinky();
void moveBlinky();
void moveClyde();
//int *handleMapChange(int reason, int *Map);
void printMap(void *Map) {
    int(*mapPtr)[columns] = Map;
    clear();
    for(int x = 0; x < columns; x++) {
        for(int y = 0; y < rows; y++) {
            printw("%d\t", mapPtr[x][y]);
        }
        printw("\n");
    }
}

