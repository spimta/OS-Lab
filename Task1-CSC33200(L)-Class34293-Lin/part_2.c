#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 50

int main(int argc, char *argv[]) {
    int fd;
    char buf[BUF_SIZE];
    int len;

    // No argument
    if (argc != 2) {
        printf("\nNeed a file name to run this command; \n");
        return 1;
    }

    // open the file
    errno = 0;
    fd = open(argv[1], O_RDONLY);

    // Open file unsuccessful
    if (fd == -1) {
        if (errno == ENOENT) {
            printf("File does not exists! \n");
        } else if (errno == EACCES) {
            printf("No permission to read the file");
        } else {
            printf("\n open() failed with error [%s]\n",strerror(errno)); 
        }
        return 1;
    }
    else {
        // open successfully, print the content
        while (len = read(fd, buf, BUF_SIZE)) {
            write(1, buf, len);
        }
    }
    close(fd);

    return 0;
}