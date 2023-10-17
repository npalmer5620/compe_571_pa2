//
// Created by Nick Palmer on 10/17/23.
//

#include "util.h"

#include <sys/unistd.h>
#include <math.h>
#include <stdio.h>


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
void find_stats(double response_time[N_TASKS]) {
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
}
