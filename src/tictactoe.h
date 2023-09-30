// Constants
#define NO_PLAYER       0
#define PLAYER_CROSS    1
#define PLAYER_ROUND    2

// Functions prototypes
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
void drawPlayer(SDL_Renderer* renderer, int playerID, int x, int y);
void drawBoard(SDL_Renderer* renderer, int board[3][3]);

int checkGameOver(int board[3][3]);
char convertPlayerToChar (int playerID);
void convertMousePositionToBoardPosition(int mouseX, int mouseY, int * boardX, int * boardY);
