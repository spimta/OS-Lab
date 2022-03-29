#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t cpid = fork(); // fork

    // fork failed
    if (cpid < 0)
    {
        perror("Fork not successful");
        return 1;
    }

    // child process
    if (cpid == 0)
    {

        // execute ls file to show all file using execvp
        char *args[3];
        args[0] = "";
        args[1] = "-la"; // argument to show hidden file and permission
        args[2] = NULL;
        execvp("ls", &args[0]);
        return 0;
    }

    // parent process
    else
    {
        wait(&status);                                // wait for child process
        printf("pid of child process is %d\n", cpid); // print pid of child process
    }

    return 0;
}
