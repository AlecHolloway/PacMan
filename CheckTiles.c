#include "consts.h"

int checkUpTile(int currentRow, int currentCol, int Map[][columns]) {
    int upTile = Map[currentRow - 1][currentCol];
         if (currentRow > 0 && upTile == Wall) { return Wall; }
    else if (currentRow > 0 && upTile == Ghost) { return Ghost; }
    else if (currentRow > 0 && upTile == Empty) { return Empty; }
    else if (currentRow > 0 && upTile == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && upTile == Pellet) { return Pellet; }
}
int checkDownTile(int currentRow, int currentCol, int Map[][columns]) {
    int downTile = Map[currentRow + 1][currentCol];
         if (currentRow >= 0 && downTile == Wall) { return Wall; }
    else if (currentRow >= 0 && downTile == Ghost) { return Ghost; }
    else if (currentRow >= 0 && downTile == Empty) { return Empty; }
    else if (currentRow >= 0 && downTile == PowerPellet) { return PowerPellet; }
    else if (currentRow >= 0 && downTile == Pellet) { return Pellet; }
}
int checkLeftTile(int currentRow, int currentCol, int Map[][columns]) {
    int leftTile = Map[currentRow][currentCol - 1];
         if (currentRow > 0 && leftTile == Wall) { return Wall; }
    else if (currentRow > 0 && leftTile == Ghost) { return Ghost; }
    else if (currentRow > 0 && leftTile == Empty) { return Empty; }
    else if (currentRow > 0 && leftTile == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && leftTile == Pellet) { return Pellet; }
}
int checkRightTile(int currentRow, int currentCol, int Map[][columns]) {
    int rightTile = Map[currentRow][currentCol + 1];
         if (currentRow > 0 && rightTile == Wall) { return Wall; }
    else if (currentRow > 0 && rightTile == Ghost) { return Ghost; }
    else if (currentRow > 0 && rightTile == Empty) { return Empty; }
    else if (currentRow > 0 && rightTile == PowerPellet) { return PowerPellet; }
    else if (currentRow > 0 && rightTile == Pellet) { return Pellet; }
}
