#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 50

int main(int argc, char *argv[]) {
    int fd;
    int fd2;
    char buf[50];
    int len;
    int len2;

    // Not enough argument
    if (argc != 3) {
        printf("\nNeed 2 parameters to run this command; \n");
        return 1;
    }

    // open the file for the source file
    errno = 0;
    fd = open(argv[1], O_RDONLY);

    // failed to open the source file
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

    // open the source file successfully
    else {

        // open the destination file
        fd2 = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        
        // fail to opent he destination file
        if (fd2 == -1) {
            printf("failed to open file %s", argv[2]);
            perror("Error: ");
            return 1;
        }

        // open successsfully
        else {

            // write the content of source file into the desitnation file
            while (len = read(fd, buf, BUF_SIZE)) {
                len2 = write(fd2, buf, len);
            }
        }
    }

    close(fd);
    close(fd2);

    return 0;
}