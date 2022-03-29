#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

// pthread mutex
pthread_mutex_t lock;
pthread_mutex_t agent_mutex;
pthread_mutex_t smoker_tabacco_mutex;
pthread_mutex_t smoker_paper_mutex;
pthread_mutex_t smoker_match_mutex;

// thread
pthread_t agent_thrd;
pthread_t smoker_tabacco_thrd;
pthread_t smoker_paper_thrd;
pthread_t smoker_match_thrd;

// agent function for agent thread
void *agent_func(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock); // lock all other thread, or when other thread is runing wait until it's to be free
        srand(time(NULL));
        int randNum = rand() % 3 + 1;

        if (randNum == 1)
        {
            printf("Agent put match on table. \n");
            printf("Agent put paper on table. \n");
            pthread_mutex_unlock(&smoker_tabacco_mutex); // unlock smoker with tabacco
        }
        else if (randNum == 2)
        {
            printf("Agent put tabacco on table. \n");
            printf("Agent put match on table. \n");
            pthread_mutex_unlock(&smoker_paper_mutex); // unlock smoker with paper
        }
        else
        {
            printf("Agent put paper on table \n");
            printf("Agent put tabacco on table \n");
            pthread_mutex_unlock(&smoker_match_mutex); // unlock smoker with match
        }
        pthread_mutex_unlock(&lock); // free the lock that for other process can run
        pthread_mutex_lock(&agent_mutex); // lock the agent to prevent the agent runs two times consecutively, wait for a smoker pick up materials on the table
    }
}

// smoker tabacco function for smoker thread
void *smoker_tabacco_func(void *arg)
{
    srand(time(NULL));
    while (1)
    {
        pthread_mutex_lock(&smoker_tabacco_mutex); // lock the process when smoker tabacco is 0, since it's 1, it means table has the materials that smoker tabaccos needs
        pthread_mutex_lock(&lock); // lock semaphore to prevent 2 processes runs at the same time
        printf("smoker tabacco pick up match. \n");
        printf("smoker tabacco pick up paper. \n");
        pthread_mutex_unlock(&agent_mutex); // free the agent to continues run
        pthread_mutex_unlock(&lock); // free other processes to run
        printf("smoker tabacco smoke. \n");
        sleep(rand() % 5 + 1);
    }
}

// smoker paper functon for smoker paper
void *smoker_paper_func(void *arg)
{
    srand(time(NULL));
    while (1)
    {
        pthread_mutex_lock(&smoker_paper_mutex); // lock the process when smoker paper is 0, since it's 1, it means table has the materials that smoker paper needs
        pthread_mutex_lock(&lock); // lock semaphore to prevent 2 processes runs at the same time
        printf("smoker paper pick up tabacco. \n");
        printf("smoker paper pick up match. \n");
        pthread_mutex_unlock(&agent_mutex); // free the agent to continues run
        pthread_mutex_unlock(&lock); // free other processes to run
        printf("smoker paper smoke. \n");
        sleep(rand() % 5 + 1);
    }
}

// smoker match function for smoker match
void *smoker_match_func(void *arg)
{
    srand(time(NULL));
    while (1)
    {
        pthread_mutex_lock(&smoker_match_mutex); // lock the process when smoker match is 0, since it's 1, it means table has the materials that smoker match needs
        pthread_mutex_lock(&lock); // lock semaphore to prevent 2 processes runs at the same time
        printf("smoker match pick up tabacco. \n");
        printf("smoker match pick up paper. \n");
        pthread_mutex_unlock(&agent_mutex); // free the agent to continues run
        pthread_mutex_unlock(&lock); // free other processes to run
        printf("smoker match smoke. \n"); 
        sleep(rand() % 5 + 1);
    }
}

int main()
{
    // pthread init
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&agent_mutex, NULL);
    pthread_mutex_init(&smoker_tabacco_mutex, NULL);
    pthread_mutex_init(&smoker_paper_mutex, NULL);
    pthread_mutex_init(&smoker_match_mutex, NULL);

    // initially unlock the lock mutex and all others are locked
    pthread_mutex_unlock(&lock);
    pthread_mutex_lock(&agent_mutex);
    pthread_mutex_lock(&smoker_tabacco_mutex);
    pthread_mutex_lock(&smoker_paper_mutex);
    pthread_mutex_lock(&smoker_match_mutex);

    // create and run the thread 
    pthread_create(&agent_thrd, NULL, agent_func, NULL);
    pthread_create(&smoker_tabacco_thrd, NULL, smoker_tabacco_func, NULL);
    pthread_create(&smoker_paper_thrd, NULL, smoker_paper_func, NULL);
    pthread_create(&smoker_match_thrd, NULL, smoker_match_func, NULL);

    pthread_join(agent_thrd, NULL);
    pthread_join(smoker_tabacco_thrd, NULL);
    pthread_join(smoker_paper_thrd, NULL);
    pthread_join(smoker_match_thrd, NULL);

    return 0;
}