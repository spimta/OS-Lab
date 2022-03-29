#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t cpid = fork();

    // fork failed
    if (cpid < 0)
    {
        perror("fork failed!\n");
        return 1;
    }

    // child process
    if (cpid == 0)
    {
        execl("/bin/date", "date", 0, NULL); // execute file to print date and time
        return 0;
    }

    // parent process
    else
    {
        // wait for chile process
        wait(&status);
        printf("pid of child process is %d\n", cpid); // print child pid
    }

    return 0;
}