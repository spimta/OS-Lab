#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 100

int main(int argc, char *argv[]) {
    int fd;
    int fd2;
    char buf[BUF_SIZE+3];
    int len;
    int len2;

    // open the file "source.txt" for read
    errno = 0;
    fd = open("./source.txt", O_RDONLY);

    // Failed to open the file "source.txt"
    if (fd == -1) {
        if (errno == ENOENT) {
            perror("Errror: ");
            printf("File does not exists! \n");
        } else if (errno == EACCES) {
            perror("Errror: ");
            printf("No permission to read source.txt");
        } else {
            printf("\n open() failed with error [%s]\n",strerror(errno)); 
        }
        return 1;
    }

    // open the file successfully
    else {

        // opent the file "destination.txt" for write
        fd2 = open("./destination.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (fd2 == -1) {
            printf("failed to open file destination.txt\n");
            perror("Error: ");
            return 1;
        }

        //open successfully
        else {
            
            // loop to write the content 100 character and add XYZ at the end of every 100 character
            while (len = read(fd, buf, BUF_SIZE)) {
                for (int i = 0; i < len; ++i) {
                    if (buf[i] == '1') {
                        buf[i] = 'L';
                    }
                }
                buf[len] = 'X';
                buf[len+1] = 'Y';
                buf[len+2] = 'Z';

                write(fd2, buf, len+3);

            }
        }
    }
    close(fd);
    close(fd2);

    return 0;
}