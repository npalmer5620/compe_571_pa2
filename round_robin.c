#include "util.h"

// Workloads for each task: Task 1, Task 2, Task 3, Task 4
// Workload is always sorted from most to least intensive
const int WORKLOADS[N_TASKS] = {100000, 50000, 25000, 10000};
const int QUANTUMS[N_TASKS] = {7500, 10000, 30000, 60000};

double round_robin(int iterations)
{
	double *task_response_times[N_TASKS];

	for (size_t i = 0; i < N_TASKS; i++)
	{
		task_response_times[i] = (double *)malloc(sizeof(double) * iterations);
	}

	for (size_t iter = 0; iter < iterations; iter++)
	{
		struct timespec start, end[N_TASKS];
		pid_t task_pids[N_TASKS];
		int run_state[N_TASKS] = {1, 1, 1, 1};
		int prev_run_state[N_TASKS] = {1, 1, 1, 1};
		int tasks_left = N_TASKS;

		create_and_suspend_tasks(task_pids, WORKLOADS);

		printf("Iter %ld | tasks created\n", iter);

		/************************************************************************************************
			At this point, all  newly-created child processes are stopped, and ready for scheduling.
		*************************************************************************************************/

		/************************************************************************************************
			- Scheduling code starts here
			- Below is a sample schedule. (which scheduling algorithm is this?)
			- For the assignment purposes, you have to replace this part with the other scheduling methods
			to be implemented.
		************************************************************************************************/

		clock_gettime(CLOCK_MONOTONIC, &start);

		// Run all tasks until they are all finished
		while (tasks_left > 0)
		{
			// Check if any tasks are ready to run
			for (size_t i = 0; i < N_TASKS; i++)
			{
				if (run_state[i] > 0)
				{
					// Resume task, run for quantum, suspend task
					kill(task_pids[i], SIGCONT);
					usleep(QUANTUMS[i]);
					kill(task_pids[i], SIGSTOP);

					// Update run state of task
					waitpid(task_pids[i], &run_state[i], WNOHANG);

					// Check if run state changed
					if (run_state[i] != prev_run_state[i])
					{
						// Run state changed, so record end time
						clock_gettime(CLOCK_MONOTONIC, &end[i]);
						tasks_left--;
					}
				}
			}
		}

		/************************************************************************************************
			- Scheduling code ends here
		************************************************************************************************/

		for (int i = 0; i < N_TASKS; ++i)
		{
			task_response_times[i][iter] = end[i].tv_sec - start.tv_sec + ((end[i].tv_nsec - start.tv_nsec) / 1000000000.0);
		}
	}

	return find_stats2d(task_response_times, iterations);
}