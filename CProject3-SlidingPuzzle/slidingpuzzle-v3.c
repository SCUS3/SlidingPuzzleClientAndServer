#include <errno.h>
#include "sp-pipe-server.h"
#include "sp-pipe-client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "sp-pipe-client.h"

/*
* Initializing two pipes and buffer
* @var clientToServer: sends commands from client to server
* @var serverToClient: sends back the results from the server back to the client
*/
int clientToServer[2];
int serverToClient[2];
// char buffer[999];

/*
 * @main method calls the initialization and acceptInput methods
*/
int main(int argc, char **argv)
{
    pid_t game;

    pipe(clientToServer);
    pipe(serverToClient);
    game = fork();
    if (game == 0)
    {
        close(clientToServer[1]);
        close(serverToClient[0]);
        client();
    }
    else if(game == -1)
    {
        printf("\nPipe has failed\n");
        return 1;
    }
    else
    {
        close(serverToClient[0]);
        close(clientToServer[1]);
        server();
    }
    return 0;
}

// int main(int argc, char **argv)
// {
//     game;

//     if (pipe(clientToServer) == -1)
//     {
//         printf("\nPipe Failed");
//         return 1;
//     }
//     if (pipe(serverToClient) == -1)
//     {
//         printf("\nPipe Failed");
//         return 1;
//     }
//     game = fork();
//     if (game == 0)
//     {
//         client();
//     }
//     else
//     {
//     server();
//     }
// }
