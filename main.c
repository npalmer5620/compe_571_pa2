#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "round_robin.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./PA2 <scheduler> <n-trials>\n");
        printf("Scheduler options: [fcfs, rr, sjf, mlfq]\n");
        exit(1);
    }

    if (atoi(argv[2]) <= 0 || atoi(argv[2]) > 100)
    {
        printf("n-trials must be between 1 and 100\n");
        exit(1);
    }

    if (strcmp("fcfs", argv[1]) == 0)
    {
        /* code */
    }
    else if (strcmp("rr", argv[1]) == 0)
    {
        printf("Running Round Robin Scheduler with %d iterations\n", atoi(argv[2]));
        round_robin(atoi(argv[2]));
    }
    else if (strcmp("sjf", argv[1]) == 0)
    {
        /* code */
    }
    else if (strcmp("mlfq", argv[1]) == 0)
    {
        /* code */
    }
    else
    {
        printf("Scheduler options: [fcfs, rr, sjf, mlfq]\n");
        exit(1);
    }

    return 0;
}
