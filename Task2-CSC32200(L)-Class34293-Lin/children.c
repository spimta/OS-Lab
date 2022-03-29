#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t cpid1 = fork();

    // Fork error
    if (cpid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0)
    {
        // Code for child 1
        printf("I am child one, my pid is: %d\n", getpid());
    }
    else
    {
        pid_t cpid2 = fork();

        // Fork error
        if (cpid2 == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid2 == 0)
        {
            // Code for child 2
            printf("I am child two, my pid is: %d\n", getpid());
        }
        else
        {
            // Wait for 2 child process end
            waitpid(cpid1, NULL, 0);
            waitpid(cpid2, NULL, 0);
        }
    }

    return 0;
}