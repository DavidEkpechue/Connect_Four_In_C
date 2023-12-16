#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ROWS 6
#define COLS 7

// Player structure
typedef struct {
    char symbol;  // Player's symbol 
} Player;

// Function to display the Connect Four grid
void displayGrid(char grid[ROWS][COLS]) 
{
    // Iterate over each row
    for (int i = 0; i < ROWS; i++) 
    {
        // Iterate over each column
        for (int j = 0; j < COLS; j++) 
        {
            // Print the content of the current cell
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");

        // Print horizontal dividers between rows
        for (int j = 0; j < COLS; j++) 
        {
            printf("-----");
        }
        printf("-\n");
    }
}

// Function to update the grid with a player's move
void PlayerMove(char grid[ROWS][COLS], int column, Player *player) 
{
    // Iterate over rows
    for (int i = ROWS - 1; i >= 0; i--) 
    {
        // Check if current cell is empty
        if (grid[i][column] == ' ') 
        {
            // Place the player's symbol in the current cell
            grid[i][column] = player->symbol;
            break;
        }
    }
}

int checkWin(char grid[ROWS][COLS], char symbol) 
{
    // Check horizontal lines
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (grid[i][j] == symbol &&
                grid[i][j+1] == symbol &&
                grid[i][j+2] == symbol &&
                grid[i][j+3] == symbol) {
                return 1; // Win condition
            }
        }
    }

    // Check vertical lines
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == symbol &&
                grid[i+1][j] == symbol &&
                grid[i+2][j] == symbol &&
                grid[i+3][j] == symbol) {
                return 1; // Win condition
            }
        }
    }

    // Check diagonal lines
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (grid[i][j] == symbol &&
                grid[i+1][j+1] == symbol &&
                grid[i+2][j+2] == symbol &&
                grid[i+3][j+3] == symbol) {
                return 1; // Win condition
            }
        }
    }

    // Check diagonal lines (from top-right to bottom-left)
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = COLS - 1; j >= 3; j--) {
            if (grid[i][j] == symbol &&
                grid[i+1][j-1] == symbol &&
                grid[i+2][j-2] == symbol &&
                grid[i+3][j-3] == symbol) {
                return 1; // Win condition met
            }
        }
    }

    return 0; // No win condition found
}


int main() 
{
    char grid[ROWS][COLS];

    Player player1;
    Player player2;

    player1.symbol = 'X';
    player2.symbol = 'O';

    // Initialize grid
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            grid[i][j] = ' ';
        }
    }

    int currentPlayer = 1;
    int column;

    // Game loop
    while (1) 
    {
        // Display the current grid
        displayGrid(grid);

        // Determine the current player
        Player *currentPlayerPtr;
        if (currentPlayer == 1) 
        {
            currentPlayerPtr = &player1;
        } else 
        {
            currentPlayerPtr = &player2;
        }

        // Get the column choice from the current player
        printf("Player %d, choose a column (1-%d): ", currentPlayer, COLS);
        scanf("%d", &column);

        // Subtract 1 from the column to match array indexing
        column--;

        // Check if the column choice is valid
        if (column < 0 || column >= COLS) 
        {
            printf("Invalid column. Please choose again.\n");
            continue;
        }

        // Make the player's move
        PlayerMove(grid, column, currentPlayerPtr);

        if (checkWin(grid, currentPlayerPtr->symbol)) 
        {
        printf("Player %d wins!\n", currentPlayer);
        break;  // Exit the game loop
        }

        // Switch to the next player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
