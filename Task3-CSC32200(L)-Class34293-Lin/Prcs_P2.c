#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 150

int main(int argc, char *argv[])
{
    int fd;
    int fd2;
    int fd3;
    char buf[BUF_SIZE];
    int len;

    // open the file "source.txt" for read
    errno = 0;
    fd = open("./source.txt", O_RDONLY);

    // Failed to open the file "source.txt"
    if (fd == -1)
    {
        if (errno == ENOENT)
            perror("Errror: File does not exists\n");

        else if (errno == EACCES)
            perror("Errror: No permission to read source.txt");

        else
            printf("\n open() failed with error [%s]\n", strerror(errno));

        return 1;
    }

    // open the file source.txt successfully
    // open the file "destination1.txt" for write
    fd2 = open("./destination1.txt", O_WRONLY);

    // open destination1.txt failed
    if (fd2 == -1)
    {
        if (errno == ENOENT)
            perror("file does not exists! \n");

        else if (errno == EACCES)
            perror("file does not have write permission! \n");

        else
            perror("open() failed! \n");

        return 1;
    }

    // open the file destination2.txt for write
    fd3 = open("./destination2.txt", O_WRONLY);

    // failed to open the file
    if (fd3 == -1)
    {
        if (errno == ENOENT)
            perror("file does not exists! \n");

        else if (errno == EACCES)
            perror("file does not have write permission! \n");

        else
            perror("open() failed! \n");

        return 1;
    }

    // loop to write the content 100 character and add XYZ at the end of every 100 character
    while (1)
    {
        len = read(fd, buf, 100); // read 100 character into the buffer

        // replace 1 with L in the buffer
        for (int i = 0; i < len; ++i)
        {
            if (buf[i] == '1')
            {
                buf[i] = 'L';
            }
        }
        write(fd2, buf, len); // write the modified buffer content into the file destination1.txt

        // check whether process the end of the file
        if (len < 100)
            break;

        len = read(fd, buf, 50); // read 50 character into the buffer

        // replace 3 with E in the buffer
        for (int i = 0; i < len; ++i)
        {
            if (buf[i] == '3')
            {
                buf[i] = 'E';
            }
        }
        write(fd3, buf, len); // write the modified buffer content into the file destination2.txt

        // check whether process the end of the file
        if (len < 50)
            break;
    }

    close(fd);
    close(fd2);
    close(fd3);

    return 0;
}