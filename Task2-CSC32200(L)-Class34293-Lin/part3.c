#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Parent process
    if (argc != 2)
    {
        printf("Need a input argument for this program! \n");
        return 1;
    }
    int num = atoi(argv[1]);

    pid_t child1 = fork();
    if (child1 == 0)
    {
        // Child1 process
        int sum = 0;

        // Loop to print sum of 0+2+...n
        for (int i = 0; i <= num; i += 2)
        {
            sum += i;
            printf("this is child process 1, current sum S1 = %d \n", sum);
        }
    }
    else
    {
        // Parent process
        pid_t child2 = fork();
        if (child2 == 0)
        {
            // Child2 process
            int sum = 0;

            // Loop to print sum of 1+3+...+n
            for (int i = 1; i <= num; i += 2)
            {
                sum += i;
                printf("this is child process 2, current sum S2 = %d \n", sum);
            }
        }
        else
        {

            // parent process
            int sum = 0;

            // Loop to print 0+1+...+n
            for (int i = 0; i <= num; i++)
            {
                sum += i;
                printf("this is parent process, current sum S3 = %d \n", sum);
            }
        }
    }

    return 0;
}