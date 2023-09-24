#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Simple SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Event loop
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    // Clean up and quit
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

#define NO_PLAYER       0
#define PLAYER_CROSS    1
#define PLAYER_ROUND    2

int checkGameOver(int board[3][3]) {

    int i;

    // Check horizontal wins
    for (i = 0; i < 3; i++)
        if ( (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] != NO_PLAYER) )
            return board[i][0];

    // Check vertical wins
    for (i = 0; i < 3; i++)
        if ( (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[0][i] != NO_PLAYER) )
            return board[0][i];

    // Check diagonal wins
    if ( (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != NO_PLAYER) )
        return board[0][0];
    if ( (board[2][0] == board[1][1]) && (board[1][1] == board[0][2]) && (board[2][0] != NO_PLAYER) )
        return board[2][0];

    // If we found no winners : we return NO_PLAYER
    return NO_PLAYER;
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

char convertPlayerToChar (int winner) {

    if (winner == PLAYER_CROSS) {
        return 'X';
    }
    else {
        return 'O';
    }

}

int main() {
    int board[3][3];
    int i, j;
    int playerTurn = PLAYER_CROSS;
    int x_pos = 0;
    int y_pos = 0;

    // Let's init the board first
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            board[i][j] = NO_PLAYER;

    // Display the board
    printGame(board);

    while(checkGameOver(board) == NO_PLAYER) {

        // Get input
        printf("Enter X position: ");
        scanf("%d", &x_pos);

        printf("\n");

        printf("Enter Y position : ");
        scanf("%d", &y_pos);

        board[y_pos][x_pos] = playerTurn;

        if (playerTurn == PLAYER_CROSS) {
            playerTurn = PLAYER_ROUND;
        }
        else {
            playerTurn = PLAYER_CROSS;
        }

        // Display the board
        printGame(board);

    }

    char winner = convertPlayerToChar(checkGameOver(board));

    printf("\nThe winner is : %c !\n", winner);

    return 0;
}

*/
