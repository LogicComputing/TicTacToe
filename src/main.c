#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "tictactoe.h"

int main(int argc, char* argv[]) {

    // Board 2D array : contains the state of the game
    int board[3][3];
    int playerTurn = PLAYER_CROSS;
    int counter = 0;
    int gameOver = 0;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    // Let's init the board first
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = NO_PLAYER;

    // Show the first player turn
    printf("Player turn : %c\n", convertPlayerToChar(playerTurn));

    // Event loop
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONUP && gameOver == 0) {

                // Get mouse XY position in the window
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Convert this XY position into a board index
                int boardX, boardY;
                convertMousePositionToBoardPosition(mouseX, mouseY, &boardX, &boardY);

                // Check that the player can actually play here
                // It means that this index should not have already a playerID
                if (board[boardX][boardY] == NO_PLAYER) {

                    // Update the board 2D array
                    board[boardX][boardY] = playerTurn;

                    // Switch playerTurn
                    if (playerTurn == PLAYER_CROSS) {
                        playerTurn = PLAYER_ROUND;
                    }
                    else {
                        playerTurn = PLAYER_CROSS;
                    }

                    // Check if the game is over
                    int winner = checkGameOver(board);
                    if (winner != NO_PLAYER) {
                        char winner = convertPlayerToChar(checkGameOver(board));
                        printf("Game over : the winner is : %c !\n", winner);
                        gameOver = 1;
                    }

                    // Check if we have a draw
                    counter = counter + 1;
                    if ((counter == 9) && (winner == NO_PLAYER)) {
                        printf("Game over : it's a draw\n");
                        gameOver = 1;
                    }

                    // Show the first player turn
                    if (gameOver == 0) {
                        printf("Player turn : %c\n", convertPlayerToChar(playerTurn));
                    }
                }
                else {
                    printf("You can't play here. There is already a player.\n");
                }

            }
        }

        // SDL Render and draw the board
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        drawBoard(renderer, board);
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
