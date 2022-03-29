#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <error.h>

int main(int argc, char *argv[])
{
    char cmd[1000];
    int status;

    while (1)
    {
        printf("command: ");
        scanf("%[^\n]s", cmd); // read until \n
        getchar(); // get a \n from buffer for next input
        // cmd[strlen(cmd)] = '\0';

        if (strcasecmp(cmd, "quit") == 0) // if cmd to be quit then finish
            return 0;

        char *args[100];
        int argsc = 0;
        char *tok;

        // parse the command to get the argument array
        tok = strtok(cmd, " ");
        args[0] = tok;
        argsc++;

        while (1)
        {
            tok = strtok(NULL, " ");
            if (tok == NULL)
                break;
            args[argsc] = tok;
            argsc++;
        }
        args[argsc] = NULL;

        // fork
        pid_t cpid = fork();

        if (cpid == -1)
        {
            // fork error
            perror("fork unsuccessful! \n");
        }
        if (cpid == 0)
        {
            // child process to execute the file
            int v = execvp(args[0], &args[0]);

            // failed to execute
            if (v == -1)
            {
                perror("failed to execute file");
                return 1;
            }
        }
        else
        {
            // parent process
            wait(&status); // wait for child process
        }
    }

    return 0;
}