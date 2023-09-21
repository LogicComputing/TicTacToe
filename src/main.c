#include <stdio.h>
#include <stdlib.h>

#define NO_PLAYER       0
#define PLAYER_CROSS    1
#define PLAYER_ROUND    2

int checkGameOver(int board[3][3]) {

    int gameWinner = NO_PLAYER;
    int i;

    // Check horizontal wins

    // Check vertical wins

    // Check diagonal wins

    return gameWinner;
}

void printGame(int board[3][3]) {
    int i;
    int j;

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            if (board[i][j] == NO_PLAYER) {
                printf("|-|");
            }
            else if (board[i][j] == PLAYER_CROSS) {
                printf("|X|");
            }
            else {
                printf("|O|");
            }
        }
        printf("\n");
    }
}

int main() {
    int board[3][3];
    int i, j;

    // Let's init the board first
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            board[i][j] = NO_PLAYER;

    /*
    board[0][0] = PLAYER_CROSS;
    board[0][1] = PLAYER_CROSS;
    board[0][2] = PLAYER_CROSS;
    */

    printGame(board);

    return 0;
}
