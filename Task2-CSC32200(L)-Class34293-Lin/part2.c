#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Parent process P
    int a = 10, b = 25, fq = 0, fr = 0;
    fq = fork();

    if (fq == 0)
    {
        // Child process Q
        a = a + b;
        printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());

        fr = fork();
        if (fr != 0)
        {
            // Parent process Q
            b = b + 20;
            printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());
        }
        else
        {
            // Child process R
            a = (a * b) + 30;
            printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());
        }
    }
    else
    {
        // Parent process P
        b = a + b - 5;
        printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());
    }

    return 0;
}