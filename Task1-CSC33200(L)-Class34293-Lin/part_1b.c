#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int fd;
    errno = 0;
    
    // open the file, or create and open the file if the file doesnot exsits
    char * filepath = "./destination.txt";
    fd = open(filepath, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    //open with error
    if (fd == -1) {
        printf("\n Open() failed with errror [%s] \n", strerror(errno));
        return 1;
    }
    
    // open successfully
    else {
        printf("\n open() successfully \n");
    }

    return 0;
}