#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    int fd2;
    errno = 0;

    // create a file (empty the content if the file exists) called destination1.txt with read, write, execute permission
    char *filepath = "./destination1.txt";
    fd = creat(filepath, 00777);

    // create with error
    if (fd == -1)
    {
        printf("\n creat() failed with errror [%s] \n", strerror(errno));
        return 1;
    }

    // create successfully
    else
    {
        printf("create destination1.txt successfully \n");
    }

    // create another file called destination2.txt with read, write, execute permission
    char *filepath2 = "./destination2.txt";
    fd2 = creat(filepath2, 00777);

    // create with error
    if (fd2 == -1)
    {
        printf("\n creat() failed with errror [%s] \n", strerror(errno));
        return 1;
    }

    // create successfully
    else
    {
        printf("create destination2.txt successfully \n");
    }

    return 0;
}