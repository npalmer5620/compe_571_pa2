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
#include "util.h"

/************************************************************************************************
		These DEFINE statements represent the workload size of each task and
		the time quantum values for Round Robin scheduling for each task.
*************************************************************************************************/

#define WORKLOAD1 100000
#define WORKLOAD2 50000
#define WORKLOAD3 25000
#define WORKLOAD4 10000

#define QUANTUM1 7500
#define QUANTUM2 10000
#define QUANTUM3 30000
#define QUANTUM4 60000

int main2(int argc, char const *argv[])
{
    struct timespec start, end[4];
	pid_t pid1, pid2, pid3, pid4;
	int running;
    int done;

	pid1 = fork();

	if (pid1 == 0){

		myfunction(WORKLOAD1);

		exit(0);
	}
	kill(pid1, SIGSTOP);

	pid2 = fork();

	if (pid2 == 0){

		myfunction(WORKLOAD2);

		exit(0);
	}
	kill(pid2, SIGSTOP);

	pid3 = fork();

	if (pid3 == 0){

		myfunction(WORKLOAD3);

		exit(0);
	}
	kill(pid3, SIGSTOP);

	pid4 = fork();

	if (pid4 == 0){

		myfunction(WORKLOAD4);

		exit(0);
	}
	kill(pid4, SIGSTOP);

	/************************************************************************************************
		At this point, all  newly-created child processes are stopped, and ready for scheduling.
	*************************************************************************************************/



	/************************************************************************************************
		- Scheduling code starts here
		- Below is a sample schedule. (which scheduling algorithm is this?)
		- For the assignment purposes, you have to replace this part with the other scheduling methods
		to be implemented.
	************************************************************************************************/

	running = 1;
    done = 1;

	//struct with pid and workload and reorder according to runtime (higher workload, higher runtime)
	struct Process{
		pid_t pidNum;
		int Workload;
	};
	
	pid_t pidVal[4];
	pidVal[0] = pid1;
	pidVal[1] = pid2;
	pidVal[2] = pid3;
	pidVal[3] = pid4;

	int work[4];
	work[0] = WORKLOAD1;
	work[1] = WORKLOAD2;
	work[2] = WORKLOAD3;
	work[3] = WORKLOAD4;

	struct Process process[4];
	for(int i = 0; i< 4; i++){
		process[i].pidNum = pidVal[i];
		process[i].Workload = work[i];
	}

	struct Process temp;
	for (int i = 0; i < 4; i++){
		for(int j = 0; j< 4; j++){
			if(process[i].Workload > process[j].Workload){
				temp.pidNum = process[i].pidNum;
				temp.pidNum = process[i].Workload;

				process[i] = process[j];
				process[j] = temp;
			}
		}
	}

    clock_gettime(CLOCK_MONOTONIC, &start);

	for(int i = 0; i < 4; i++){
		running = 1;
		if(running >0){
			kill(process[i].pidNum, SIGCONT);
		}
		waitpid(process[i].pidNum, &running, WNOHANG);
        if (done != running) { clock_gettime(CLOCK_MONOTONIC, &end[i]); }
	}


	/************************************************************************************************
		- Scheduling code ends here
	************************************************************************************************/
	double response_time[4];

    for (int i = 0; i < 4; ++i) {
        response_time[i] =  end[i].tv_sec - start.tv_sec + ((end[i].tv_nsec - start.tv_nsec) / 1000000000.0);
    }

    find_stats(response_time);

	return 0;
}