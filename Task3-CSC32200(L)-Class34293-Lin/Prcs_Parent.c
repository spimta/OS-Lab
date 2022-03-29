#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t cpid;
    cpid = fork(); // fork child 1

    // fork failed
    if (cpid < 0)
    {
        perror("Fork error! \n");
        return 1;
    }

    // child process 1 to execute Prcs_P1
    if (cpid == 0)
    {
        char *args[2];
        args[0] = "./Prcs_P1";
        args[1] = NULL;
        execv("./Prcs_P1", &args[0]);
    }

    // parent process
    else
    {
        sleep(1);                        // sleep to wait child 1 execute
        printf("child1 pid for step 1: %d\n", cpid); // print pid of child process 1

        pid_t cpid2 = fork(); // fork child 2

        // fork failed
        if (cpid2 < 0)
        {
            perror("Fork error\n");
            return 1;
        }

        // child 2 process to run Prcs_P2
        if (cpid2 == 0)
        {
            char *args[2];
            args[0] = "./Prcs_P2";
            args[1] = NULL;
            execv("./Prcs_P2", &args[0]);
        }

        // parent process
        else
        {
            sleep(1);                                    // sleep to wait child 2 execute
            printf("child2 pid for step 2: %d\n", cpid2); // pritn pid of child process 2
        }
    }
    return 0;
}