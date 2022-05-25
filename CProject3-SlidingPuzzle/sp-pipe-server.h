#include <stdbool.h>
#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

//Instantialize
void randomize();
bool Initialization(int size);
void tearDown();
bool saveGame(char *fileName);
bool wonGame();
bool isMoveValid();
bool loadGame(char *fileName);
int moveTile();
void server();

#endif //CLIENT 