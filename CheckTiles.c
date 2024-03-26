#include "consts.h"

int checkUpTile(int currentRow, int currentCol, void *p) {
    int (*Map)[columns] = p;
    int upTile = Map[currentRow - 1][currentCol];
         if (currentRow > 0 && upTile == Wall) { return Wall; }
    else if (currentRow > 0 && upTile == Inky || upTile == Clyde || upTile == Pinky || upTile == Blinky) { return Ghost; }
    else if (currentRow > 0 && upTile == Empty) { return Empty; }
    else if (currentRow > 0 && upTile == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && upTile == Pellet) { return Pellet; }
}
int checkDownTile(int currentRow, int currentCol, void *p) {
    int (*Map)[columns] = p;
    int downTile = Map[currentRow + 1][currentCol];
         if (currentRow >= 0 && downTile == Wall) { return Wall; }
    else if (currentRow >= 0 && downTile == Inky || downTile == Clyde || downTile == Pinky || downTile == Blinky) { return Ghost; }
    else if (currentRow >= 0 && downTile == Empty) { return Empty; }
    else if (currentRow >= 0 && downTile == PowerPellet) { return PowerPellet; }
    else if (currentRow >= 0 && downTile == Pellet) { return Pellet; }
}
int checkLeftTile(int currentRow, int currentCol, void *p) {
    int (*Map)[columns] = p;
    int leftTile = Map[currentRow][currentCol - 1];
         if (currentRow > 0 && leftTile == Wall) { return Wall; }
    else if (currentRow > 0 && leftTile == Inky || leftTile == Clyde || leftTile == Pinky || leftTile == Blinky) { return Ghost; }
    else if (currentRow > 0 && leftTile == Empty) { return Empty; }
    else if (currentRow > 0 && leftTile == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && leftTile == Pellet) { return Pellet; }
}
int checkRightTile(int currentRow, int currentCol, void *p) {
    int (*Map)[columns] = p;
    int rightTile = Map[currentRow][currentCol + 1];
         if (currentRow > 0 && rightTile == Wall) { return Wall; }
    else if (currentRow > 0 && rightTile == Inky || rightTile == Clyde || rightTile == Pinky || rightTile == Blinky) { return Ghost; }
    else if (currentRow > 0 && rightTile == Empty) { return Empty; }
    else if (currentRow > 0 && rightTile == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && rightTile == Pellet) { return Pellet; }


}
