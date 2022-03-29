#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    // int status;
    int x = 2;
    int y = 2;
    int lines = 10;
    double **grades = (double **)malloc(sizeof(double *) * lines); // 2d array to store grades
    for (int i = 0; i < lines; i++)
        grades[i] = (double *)malloc(sizeof(double) * x * y);

    FILE *grades_file = fopen("grades.txt", "r"); // open grades.txt for read

    // read the grades into the array
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < x * y; j++)
        {
            fscanf(grades_file, "%lf", *(grades + i) + j);
        }
    };

    // loop to create manager process
    for (int i = 0; i < x; i++)
    {
        pid_t cpid = fork();
        if (cpid == 0)
        {
            // manager process
            // printf("manager #%d: pid-%d\n", i + 1, getpid());
            // loop to create worker process
            for (int j = 0; j < y; j++)
            {
                pid_t cpid2 = fork();
                if (cpid2 == 0)
                {
                    // worker process
                    // printf("worker #%d-%d:\n", i + 1, j + 1);
                    double total = 0;
                    int index = i * x + j; // get the index for the grades for current students
                    for (int k = 0; k < lines; k++)
                    {
                        total += grades[k][index];
                    }
                    double avg = total / lines;
                    printf("Average of chapter #%d hw #%d is: %f\n", i + 1, j + 1, avg); // printout the average
                    return 0;
                }
                else
                {
                    // parent process: do nothing, continue loop
                    // wait(&status);
                }
            }
            return 0;
        }
        else
        {
            // parent process: do nothing cotinue loop
            // wait(&status);
        }
    }

    return 0;
}