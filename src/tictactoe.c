#include <SDL2/SDL.h>
#include "tictactoe.h"

// Function to draw a circle on an SDL renderer.
//
// Parameters:
// - renderer: The SDL_Renderer where the circle will be drawn.
// - centerX, centerY: The coordinates of the circle's center.
// - radius: The radius of the circle.
//
// Thanks ChatGPT
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    // Draw the initial points on each quadrant
    SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);

    // Draw the circle using the Bresenham's algorithm
    while (x >= y) {
        y++;

        // Update the radius error
        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }

        // Draw the corresponding points on each quadrant
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);

        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
    }
}

// Function to draw player object : cross or round
void drawPlayer(SDL_Renderer* renderer, int playerID, int x, int y) {
    if (playerID == PLAYER_CROSS) {
        SDL_RenderDrawLine(renderer, 50+(x*213), 30+(y*160), 150+(x*213), 130+(y*160));
        SDL_RenderDrawLine(renderer, 150+(x*213), 30+(y*160), 50+(x*213), 130+(y*160));
    }
    else if (playerID == PLAYER_ROUND) {
        drawCircle(renderer, 106*(2*x+1), 80*(2*y+1), 70);
    }
}

// Function to draw the board
//
// It first draws the vertical and horizontal lines
// Then it draws the player : cross, round or nothing
//
// Parameters:
// - renderer: The SDL_Renderer where the board will be drawn.
// - board: a 2D array that contains the state of the board
void drawBoard(SDL_Renderer* renderer, int board[3][3]) {

    // Draw the vertical and horizontal lines
    SDL_RenderDrawLine(renderer, 213, 0, 213, 480);
    SDL_RenderDrawLine(renderer, 426, 0, 426, 480);
    SDL_RenderDrawLine(renderer, 0, 160, 640, 160);
    SDL_RenderDrawLine(renderer, 0, 320, 640, 320);

    // Draw the players
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            drawPlayer(renderer, board[i][j], i, j);
        }
    }
}

// Function to get the char of the winner
// Round -> 'O'
// Cross -> 'X'
// I prefer to print the char instead of the ID
char convertPlayerToChar (int playerID) {

    if (playerID == PLAYER_CROSS) {
        return 'X';
    }
    else {
        return 'O';
    }

}

// Function to convert the mouse position to a valid board index
//
// Parameters:
//  - mouseX, mouseY: Mouse position from the SDL_GetMouseState function
//  - boardX, boardY: Results of the function
void convertMousePositionToBoardPosition(int mouseX, int mouseY, int * boardX, int * boardY) {

    // X Position to board index
    if (mouseX < 213) {
        *boardX = 0;
    }
    else if (mouseX > 426) {
        *boardX = 2;
    }
    else {
        *boardX = 1;
    }

    // Y Position to board index
    if (mouseY < 160) {
        *boardY = 0;
    }
    else if (mouseY > 320) {
        *boardY = 2;
    }
    else {
        *boardY = 1;
    }

}

int checkGameOver(int board[3][3]) {

    // Check horizontal wins
    for (int i = 0; i < 3; i++)
        if ( (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] != NO_PLAYER) )
            return board[i][0];

    // Check vertical wins
    for (int i = 0; i < 3; i++)
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
