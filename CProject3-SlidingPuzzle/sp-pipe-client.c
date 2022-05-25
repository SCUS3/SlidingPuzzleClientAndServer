#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "sp-pipe-server.h"

//Declare
int i, j;
int tile, tileRow, tileCollumn;
int tempRow, tempCollumn;
int tempRand;
int count, tileCount, userSize, tileSize;
int gamePieces;
int **gameBoard;
char userInput;
char player[1000];
// void client();
char message[1000];



extern int clientToServer[2];
extern int serverToClient[2];

/*
* Displays gameboard information
* Conditionals used to print array string in place of the empty space
*/
void displayGameState()
{
    for (i = 0; i < userSize; i++)
    {
        for (j = 0; j < userSize; j++)
        {
            printf("%3d", gameBoard[i][j]);
        }
        printf("\n");
    }
}

/*
* If the move passes the isMoveValid condition, this method does the swap
*/
void acceptInput()
{
    enum command
{
    p,
    m,
    n,
    s,
    l,
    q
} userInput;
    do
    {
        printf("Menu, [p]rint, [m]ove, [q]uit, [n]ew, [s]ave, [l]oad \n");
        scanf(" %c", &userInput);
        if (userInput != 'p' && userInput != 'm' && userInput != 'q' && userInput != 'n' && userInput != 's' && userInput != 'l')
        {
            printf("\nERROR: Invalid Input! Please enter a valid parameter.\n");
        }
        else if (userInput == 'p')
        {
            displayGameState();
        }
        else if (userInput == 'm')
        {
            //char message[100];
            write(clientToServer[1], &message, sizeof(message));
            write(clientToServer[1], &gameBoard, sizeof(gameBoard));
            read(serverToClient[0],&gameBoard, sizeof(gameBoard));
            // if (isMoveValid(gameBoard))
            // {
            //     moveTile();
            // }
        }
        else if (userInput == 'n')
        {
            fprintf(stdout, "\nEnter dimensions of the GameBoard (3-10): \n");
            int tempSize;
            scanf("%d", &tempSize);
            write(clientToServer[1], &userInput, sizeof(userInput));
            write(clientToServer[1], &tempSize, sizeof(tempSize));
            bool result;
            read(serverToClient[0], &result, sizeof(result));
            if (result)
            {
                printf("New board created.\n");
            }
            else
            {
                printf("An Error Occurred.\n");
            }
        }
        else if (userInput == 's')
        {
            //char arr[100];
            printf("\nEnter file Name: \n");
            write(clientToServer[1], &player, sizeof(message));
            write(clientToServer[1], &userSize, sizeof(userSize));
            read(clientToServer[1], &userSize, sizeof(userSize));

        }
        else if (userInput == 'l')
        {
            char arr[100];
            printf("\nEnter file Name: \n");
            scanf("%s", arr);
            loadGame(arr);
        }
        wonGame();
    } while (userInput != 'q');
    if (userInput == 'q')
    {
        exit(0);
    }
}
/*
* Method calling AcceptInput method
*/
void client()
{
    acceptInput();
    fprintf(stdout, "Please input an integer for the size of your board!\n");
    int tempSize;
    scanf("%d", &tempSize);
        write(clientToServer[1], &message, sizeof(message));
    write(clientToServer[1], &tempSize, sizeof(tempSize));
    bool result;
    read(serverToClient[0], &result, sizeof(result));

    if (result)
    {
        printf("Created new board!\n");
    }
    else
    {
        printf("An Error Occurred.\n");
    }
}
