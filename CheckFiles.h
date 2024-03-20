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
