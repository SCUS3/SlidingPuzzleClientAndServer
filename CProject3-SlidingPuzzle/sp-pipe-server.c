#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "sp-pipe-client.h"


//Declare Global Variables
int i, j;
int tile, tileRow, tileCollumn;
int tempRow, tempCollumn;
int tempRand;
int count, tileCount, userSize, tileSize;
int gamePieces;
int **gameBoard;
char userInput;
char player[999];

extern int clientToServer[2];
extern int serverToClient[2];
// extern int pipeOne;
// extern int pineTwo;
extern char buffer[999];

/*
* Shuffles game pieces
*/
void randomize()
{
    int count = 0;
    srand(time(NULL));
    int randRow;
    int randCollumn;
    for (i = 0; i < tileRow; i++)
    {
        for (j = 0; j < tileCollumn; j++)
        {
            randRow = (rand() % (tileRow));
            randCollumn = (rand() % (tileCollumn));
            tempRand = gameBoard[randRow][randCollumn];
            gameBoard[randRow][randCollumn] = gameBoard[i][j];
            gameBoard[i][j] = tempRand;
        }
    }
}

/*
* Checks initialization of Sliding Puzzle Game
* Sets up game board using Memory Allogation
* @param size represents the dynamic size of the gamePuzzle array  
*/
bool Initialization(int size)
{
    if (size > 10 || size < 2)
        return false;
    userSize = size;
    int i, j;
    //message("Setting up Game...");

    tileRow = userSize;
    tileCollumn = userSize;
    tile = (((userSize * userSize)) - 1);
    gameBoard = malloc(sizeof(int *) * userSize);
    for (i = 0; i < userSize; i++)
    {
        gameBoard[i] = malloc(sizeof(int) * userSize);
    }
    for (i = 0; i < tileRow; i++)
    {
        for (j = 0; j < tileCollumn; j++)
        {
            gameBoard[i][j] = tile;
            tile--;
        }
    }
    randomize();
    return true;
}

/*
* Ends Sliding Puzzle Game
*/
void tearDown()
{
    //message("Ending the game...");

    for (int i = 0; i < userSize; i++)
    {
        for (int j = 0; j < userSize; j++)
        {
            free(gameBoard[i, j]);
        }
    }
}

//CONDITIONALS/LOGIC for isMoveValid:
//tempRow - TileRow = 1 <-> Tile is above empty space
//tempRow - TileRow = -1 <-> Tile is below empty space
//tempCollumn - tileCollumn = 1 <-> Tile is to the left of empty space
//tempCollumn - tileCollumn = -1 <-> Tile is to the right of empty space

/*
* Itterates through 2D array and checks whether a tile can be moved
* @param tile: tile index to move
* @return 1 if tile is movable, and -1 if not.
*/
bool isMoveValid()
{
    //message("Select valid puzzle number to move (1-15): \n");
    scanf("%d", &tile);
    for (i = 0; i < userSize; i++)
    {
        for (j = 0; j < userSize; j++)
        {
            if (gameBoard[i][j] == 0)
            {
                tempRow = i;
                tempCollumn = j;
            }
            if (gameBoard[i][j] == tile)
            {
                tileRow = i;
                tileCollumn = j;
            }
        }
    }
    if (tempRow - tileRow == 1 && tempCollumn == tileCollumn)
    {
        //message("Tile is above empty space\n");
        return true;
    }
    if (tempRow - tileRow == -1 && tempCollumn == tileCollumn)
    {
        //message("Tile is below empty space\n");
        return true;
    }
    if (tempCollumn - tileCollumn == 1 && tempRow == tileRow)
    {
        //message("Tile is to the left of empty space");
        return true;
    }
    if (tempCollumn - tileCollumn == -1 && tempRow == tileRow)
    {
        //message("Tile is to the right of empty space");
        return true;
    }
    else
    {
        return false;
    }
}
/*
* @return int
* Swaps the values of the game and empty piece
*/
int moveTile()
{
    gameBoard[tempRow][tempCollumn] = tile;
    gameBoard[tileRow][tileCollumn] = 0;
    return 0;
}

/*
 * method saves the current state of the game in a file
 * @param fileName
 * user has ability to resume game in a later session
*/
bool saveGame(char *fileName)
{
    FILE *f = fopen(fileName, "w");
    if (f == NULL)
        return false;
    // message(f, "%d ", userSize);
    for (i = 0; i < userSize; i++)
    {
        for (j = 0; j < userSize; j++)
        {
            // message(f, "%d ", gameBoard[i][j]);
        }
    }
    fclose(f);
    return true;
}

bool loadGame(char *fileName)
{
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
        return false;
    int newSize;
    fscanf(f, "%d ", &newSize);
    Initialization(newSize);
    int currentTile;
    for (i = 0; i < newSize; i++)
    {
        for (j = 0; j < newSize; j++)
        {
            fscanf(f, "%d ", &currentTile);
            gameBoard[i][j] = currentTile;
        }
    }
    userSize = newSize;
    fclose(f);
    return true;
}
/*
* Method calls Initialization method
* @param 4
*/

void acceptInput()
{
    while (1)
    {
        int cmd;
        read(clientToServer[1], &cmd, sizeof(cmd));
        if (cmd == 0)
        {
            int tempSize;
            read(clientToServer[1], &tempSize, sizeof(tempSize));
            int result;
            if (Initialization(tempSize))
            {
                result = true;
            }
            else
            {
                result = false;
                write(clientToServer[1], &result, sizeof(result));
            }
        }
        else if (cmd == 1)
        {

        } /// else if for every cmmd in github
    }
}

void server()
{
    Initialization(4);
    acceptInput();
    int tempSize;
    read(clientToServer[0], &tempSize, sizeof(tempSize));
    bool result;
    if (Initialization(tempSize))
    {
        result = true;
    }
    else
    {
        result = false;
        write(serverToClient[1], &result, sizeof(result));
    }
}