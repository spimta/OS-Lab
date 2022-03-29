#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"

int main()
{
    srand(time(NULL));
    int randNum;

    // create 5 semaphores
    int lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int smoker_tabacco = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int smoker_paper = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int smoker_match = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

    // initialize semaphores
    sem_create(lock, 1); // initialize lock to be 1 since one process need to be free to run at the beginning
    sem_create(smoker_tabacco, 0);
    sem_create(smoker_paper, 0);
    sem_create(smoker_match, 0);
    sem_create(agent, 0);

    pid_t agent_proc = fork();
    if (agent_proc == -1)
    {
        // fork failed!
        perror("fork");
        exit(1);
    }
    else if (agent_proc == 0)
    {
        while (1)
        {
            P(lock); // lock all other processes, or when other processes is runing wait until it's to be free
            randNum = rand() % 3 + 1;

            if (randNum == 1)
            {

                printf("Agent put match on table. \n");
                printf("Agent put paper on table. \n");
                V(smoker_tabacco); // unlock smoker with tabacco
            }
            else if (randNum == 2)
            {
                printf("Agent put tabacco on table. \n");
                printf("Agent put match on table. \n");
                V(smoker_paper); // unlock smoker with paper
            }
            else
            {
                printf("Agent put paper on table \n");
                printf("Agent put tabacco on table \n");
                V(smoker_match); // unlock smoker with match
            }
            V(lock); // free the lock that for other process can run
            P(agent); // lock the agent to prevent the agent runs two times consecutively, wait for a smoker pick up materials on the table
        }
    }
    else
    {
        pid_t smoker_tabacco_proc = fork();
        if (smoker_tabacco_proc == -1)
        {
            // fork failed!
            perror("fork");
            exit(1);
        }
        else if (smoker_tabacco_proc == 0)
        {
            // smoker tabacco process
            while (1)
            {
                P(smoker_tabacco); // lock the process when smoker tabacco is 0, since it's 1, it means table has the materials that smoker tabaccos needs
                P(lock); // lock semaphore to prevent 2 processes runs at the same time
                printf("smoker has tabacco pick up match. \n");
                printf("smoker tabacco pick up paper. \n");
                V(agent); // free the agent to continues run
                V(lock); // free other processes to run
                printf("smoker has tabacco smoke. \n");
                sleep(rand()%5+1);
            }
        }
        else
        {
            pid_t smoker_paper_proc = fork();
            if (smoker_paper_proc == -1)
            {
                // fork failed!
                perror("fork");
                exit(1);
            }
            else if (smoker_paper_proc == 0)
            {
                // smoker paper process
                while (1)
                {
                    P(smoker_paper); // lock the process when smoker paper is 0, since it's 1, it means table has the materials that smoker tabaccos needs
                    P(lock); // lock semaphore to prevent 2 processes runs at the same time
                    printf("smoker has paper pick up match. \n");
                    printf("smoker has paper pick up tabacco. \n");
                    V(agent); // free the agent to continues run
                    V(lock); // free other processes to run
                    printf("smoker has paper smoke. \n");
                    sleep(rand()%5+1);
                }
            }
            else
            {
                pid_t smoker_match_proc = fork();
                if (smoker_match_proc == -1)
                {
                    // fork failed!
                    perror("fork");
                    exit(1);
                }
                else if (smoker_match_proc == 0)
                {
                    // smoker match process
                    while (1)
                    {
                        P(smoker_match); // lock the process when smoker match is 0, since it's 1, it means table has the materials that smoker match needs
                        P(lock); // lock semaphore to prevent 2 processes runs at the same time
                        printf("smoker has match pick up tabacco. \n");
                        printf("smoker has match pick up paper. \n");
                        V(agent); // free the agent to continues run
                        V(lock); // free other processes to run
                        printf("smoker has match smoke. \n");
                        sleep(rand()%5+1);
                    }
                }
            }
        }
    }

    return 0;
}