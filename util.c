#include "util.h"

/************************************************************************************************
					DO NOT CHANGE THE FUNCTION IMPLEMENTATION
*************************************************************************************************/
void myfunction(int param){

	int i = 2;
	int j, k;

	while(i < param){
		k = i;
		for (j = 2; j <= k; j++)
		{
			if (k % j == 0){
				k = k/j;
				j--;
				if (k == 1){
					break;
				}
			}
		}
		i++;
	}
}
/************************************************************************************************/

// Function to calculate statistics on the elapsed time distribution
double find_stats(double response_time[N_TASKS]) {
    double mean = 0.0;
    double std_dev = 0.0;
    double min = response_time[0];
    double max = response_time[0];

    for (size_t i = 0; i < N_TASKS; i++) {
        // Continuous Sum for mean
        mean += response_time[i];

        // Compute min & max
        if (i != 0) {
            min = (response_time[i] < min) ? response_time[i] : min;
            max = (response_time[i] > max) ? response_time[i] : max;
        }
    }

    // Compute Mean
    mean /= N_TASKS;

    // Find variance for standard deviation
    for (size_t i = 0; i < N_TASKS; i++) {
        std_dev += pow(response_time[i] - mean, 2);
    }

    // Compute Std. Deviation
    std_dev = std_dev / N_TASKS;
    std_dev = sqrt(std_dev);

    printf("N_TASKS: %d\n", N_TASKS);
    printf("Response Times:\n");
    printf("P1: %lf s\n", response_time[0]);
    printf("P2: %lf s\n", response_time[1]);
    printf("P3: %lf s\n", response_time[2]);
    printf("P4: %lf s\n", response_time[3]);
    printf("Mean Response Time Time: %lf s\n", mean);
    printf("Standard Deviation: %lf s\n", std_dev);
    // printf("Min: %lf s \nMax: %lf s\n", min, max);

    return mean;
}

double find_stats2d(double* response_time[N_TASKS], size_t iterations) {
    double mean = 0.0;
    double std_dev = 0.0;

    double task_mean[N_TASKS];
    double task_std_dev[N_TASKS];
    double task_min[N_TASKS];
    double task_max[N_TASKS];


    for (size_t task = 0; task < N_TASKS; task++)
    {
        task_mean[task] = 0.0;
        task_std_dev[task] = 0.0;
        task_min[task] = response_time[task][0];
        task_max[task] = response_time[task][0];


        for (size_t iter = 0; iter < iterations; iter++)
        {
            mean += response_time[task][iter];
            task_mean[task] += response_time[task][iter];

            // Compute min & max
            if (iter != 0) {
                task_min[task] = (response_time[task][iter] < task_min[task]) ? response_time[task][iter] : task_min[task];
                task_max[task] = (response_time[task][iter] > task_max[task]) ? response_time[task][iter] : task_max[task];
            }
        }

        // Compute Mean
        task_mean[task] /= iterations;

        // Find variance for standard deviation
        for (size_t iter = 0; iter < iterations; iter++) {
            task_std_dev[task] += pow(response_time[task][iter] - task_mean[task], 2);
        }

        // Compute Std. Deviation
        task_std_dev[task] = task_std_dev[task] / iterations;
        task_std_dev[task] = sqrt(task_std_dev[task]);
    }

    // Compute Global Mean
    mean = mean / (N_TASKS * iterations);
    
    for (size_t task = 0; task < N_TASKS; task++)
    {
        for (size_t iter = 0; iter < iterations; iter++)
        {
            // Find variance for standard deviation
            std_dev += pow(response_time[task][iter] - mean, 2);
        }
    }

    // Compute Global Std. Deviation
    std_dev = std_dev / (iterations * N_TASKS);
    std_dev = sqrt(std_dev);

    printf("\n---Global Statistics---\n");
    printf("N_TASKS = %d | Iterations = %ld\n", N_TASKS, iterations);
    printf("Mean Response Time = %lf s | Std. Dev = %lf s\n\n", mean, std_dev);
    printf("---Task Specific Statistics---\n");

    for (size_t task = 0; task < N_TASKS; task++)
    {
        printf("P%ld | Mean = %lf s | Std. Dev = %lf s | Min = %lf s | Max = %lf s\n", (task + 1), task_mean[task], task_std_dev[task], task_min[task], task_max[task]);
    }
    
    return mean;
}

void create_and_suspend_tasks(pid_t task_pids[N_TASKS], const int workloads[N_TASKS]) {
    // Start and suspend all tasks
    for (size_t i = 0; i < N_TASKS; i++) {
        // Fork process and store pid
        task_pids[i] = fork();

        // Handle fork path and task suspension
        if (task_pids[i] == 0) {
            myfunction(workloads[i]);
            exit(0);
        } else {
            kill(task_pids[i], SIGSTOP);
        }
    }
}