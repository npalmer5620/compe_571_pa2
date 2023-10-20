#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>

#ifndef PA2_UTIL_H
#define PA2_UTIL_H

#define N_TASKS 4

void myfunction(int param);
double find_stats(double response_time[N_TASKS]);
double find_stats2d(double* response_time[N_TASKS], size_t iterations);
void create_and_suspend_tasks(pid_t task_pids[N_TASKS], const int workloads[N_TASKS]);

#endif //PA2_UTIL_H
