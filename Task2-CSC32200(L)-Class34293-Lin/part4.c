#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    // Parent process
    int pipefd[2];
    pid_t cpid;
    char buf[BUF_SIZE];

    // Pipe error
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();

    // Fork error
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        // Child process
        close(pipefd[0]); // Close unused read end
        int fd;
        errno = 0;
        int len;

        // Open a file descripter for read
        fd = open("./readme.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (fd == -1)
        {
            printf("\n open() failed with error [%s]\n", strerror(errno));
        }
        
        // Read the file content and write into pipe
        len = read(fd, &buf, BUF_SIZE);
        while (len > 0)
        {
            write(pipefd[1], &buf, len);
            len = read(fd, &buf, BUF_SIZE);
        }

        close(pipefd[1]); // Close write end
        _exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        wait(NULL); // Wait until child process end
        close(pipefd[1]); // Close unused write end
        int fd;
        errno = 0;
        int len;

        // Open the file for write
        fd = open("./readme.txt", O_WRONLY);
        if (fd == -1)
        {
            printf("\n open() failed with error [%s]\n", strerror(errno));
        }

        // Read content from the pipe, and write "Parent is writing: "+content into file
        len = write(fd, "Parent is writing: ", 19);
        while (len > 0)
        {
            len = read(pipefd[0], buf, BUF_SIZE);
            write(fd, buf, len);
        }
        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    }
}