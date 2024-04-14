//user1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct area
{
    int server_up;
    int client_up;
    int rw;
    char msg[100];
};

struct area *shmptr;

int main()
{
    int shmid;
    shmid = shmget(700, sizeof(struct area),IPC_CREAT| 0666);
    shmptr = (struct area *)shmat(shmid, NULL, 0);
    shmptr->rw = 0; // Set rw to 1 initially to allow user1 to send the first message

    while (1)
    {
        // Check if it's user1's turn to write
        while (shmptr->rw != 0)
            ;
        while(shmptr->client_up == 1)
        {
            printf("get from user 1:");
            if(strcmp(shmptr->msg, "stop") == 0) // Corrected comparison
            {
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
            }
            shmptr->server_up = 0;
            shmptr->client_up = 1;
        }
        printf("user2:");
        if(strcmp(shmptr->msg, "stop") == 0) // Corrected comparison
        {
            exit(1);
        }
        else
        {
            fgets(shmptr->msg, 100, stdin);
            shmptr->msg[strcspn(shmptr->msg, "\n")] = '\0'; // Remove trailing newline
        }

        shmptr->rw = 1;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
_-----------------------------------------------------------------------
// user2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct area
{
    int server_up;
    int client_up;
    int rw;
    char msg[100];
};

struct area *shmptr;

int main()
{
    int shmid;
    shmid = shmget(700, sizeof(struct area), 0666);
    shmptr = (struct area *)shmat(shmid, NULL, 0);
    shmptr->rw = 0; // Set rw to 1 initially to allow user1 to send the first message

    while (1)
    {
        // Check if it's user1's turn to write
        while (shmptr->rw != 1)
            ;
        while(shmptr->client_up == 0)
        {
            printf("get from user 2:");
            if(strcmp(shmptr->msg, "stop") == 0) // Corrected comparison
            {
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
            }
            shmptr->server_up = 0;
            shmptr->client_up = 1;
        }
        printf("user1:");
        if(strcmp(shmptr->msg, "stop") == 0) // Corrected comparison
        {
            exit(1);
        }
        else
        {
            fgets(shmptr->msg, 100, stdin);
            shmptr->msg[strcspn(shmptr->msg, "\n")] = '\0'; // Remove trailing newline
        }

        shmptr->rw = 0;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
