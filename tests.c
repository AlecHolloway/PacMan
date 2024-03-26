#include<assert.h>

int checkRightTile(int currentCol, int currentRow, void* p);
int checkLeftTile(int currentCol, int currentRow, void* p);
int checkUpTile(int currentCol, int currentRow, void * p);
int checkDownTile(int currentCol, int currentRow, void* p);
int main() {
    

    int test2[2][2] = { 
                       {1, 2},
                       {2, 2}
                      };

    int number = checkRightTile(0,1, test2);
    int number2 = checkRightTile(0,0, test2);
    int test3 = checkLeftTile(0,1,test2);
    int test4 = checkLeftTile(0,1,test2);
    int test5 = checkUpTile(1,0, test2);
    int test6 = checkDownTile(0,0,test2);

    assert(number2 == 2);
    assert(number == 2);
    assert(test3 == 1);
    //assert(test4 == 2);
    assert(test5 == 1);
    assert(test6 == 2);
}

