/*

Problem Statement:Implement the C program for CPU Scheduling Algorithms: Shortest Job First
(Preemptive) and Round Robin with different arrival time.
*/

#include <stdio.h>
#include <stdbool.h>

struct Process { 
	int pid; 
	int arrivalTime; 
	int burstTime; 
	int completionTime, waitingTime, turnaroundTime, responseTime, startTime; 
}ps[6];

int main() { 
	ps[0].pid = 0;
	ps[0].arrivalTime = 0;
	ps[0].burstTime = 8;
	ps[1].pid = 1;
	ps[1].arrivalTime = 1;
	ps[1].burstTime = 4;
	ps[2].pid = 2;
	ps[2].arrivalTime = 2;
	ps[2].burstTime = 2;
	ps[3].pid = 3;
	ps[3].arrivalTime = 3;
	ps[3].burstTime = 1;
	ps[4].pid = 4;
	ps[4].arrivalTime = 4;
	ps[4].burstTime = 3;
	ps[5].pid = 5;
	ps[5].arrivalTime = 5;
	ps[5].burstTime = 2;

	// main program
	int n = 6;	// total number of process
	int completed = 0;	// number of completed process
	int currentTime = 0;	// current time

	float avgTurnaroundTime = 0, avgWaitingTime = 0, avgResponseTime = 0;

	int burstTimeRemaining[6];	// contain remaining burst time of each process
	bool isCompleted[6] = { false };	// check process is completed (executed totally) or not

	// adding burst time of each process to remaing burst time array
	for(int i=0; i<n; i++) {
		burstTimeRemaining[i] = ps[i].burstTime;
	}

	while(completed != n) {
		// find process with minimum burst time in ready queue
		
		int minimum = 1e9;	// contain process with minimum burst time
		int minimumIndex = -1;	// contain index of process with minimum burst time
		for(int i=0; i<n; i++) {
			if(ps[i].arrivalTime <= currentTime && isCompleted[i] == false) {
				if(burstTimeRemaining[i] < minimum) {
					minimum = burstTimeRemaining[i];
					minimumIndex = i;
				}	
				if(burstTimeRemaining[i] == minimum) {
					if(ps[i].arrivalTime < ps[minimumIndex].arrivalTime) {
						minimum = burstTimeRemaining[i];
						minimumIndex = i;
					}
				}
			}
		}

		if(minimumIndex == -1) {
			currentTime++;
		}
		else {
			if(burstTimeRemaining[minimumIndex] == ps[minimumIndex].burstTime) {
				ps[minimumIndex].startTime = currentTime;
			}

			burstTimeRemaining[minimumIndex] -=1;
			currentTime++;

			if(burstTimeRemaining[minimumIndex] == 0) {
				ps[minimumIndex].completionTime = currentTime;
				ps[minimumIndex].turnaroundTime = ps[minimumIndex].completionTime - ps[minimumIndex].arrivalTime;
				ps[minimumIndex].waitingTime = ps[minimumIndex].turnaroundTime - ps[minimumIndex].burstTime;
				ps[minimumIndex].responseTime = ps[minimumIndex].startTime - ps[minimumIndex].arrivalTime;

				avgTurnaroundTime += ps[minimumIndex].turnaroundTime;
				avgWaitingTime += ps[minimumIndex].waitingTime;
				avgResponseTime += ps[minimumIndex].responseTime;

				completed++;
				isCompleted[minimumIndex] = true;
			}
		}
	}

	printf("PID \t AT \t BT \t TT \t WT \t CT \t RT\n");
	for(int i=0; i<n; i++) {
		printf("%d \t %d \t %d \t %d \t %d \t %d \t %d\n", ps[i].pid, ps[i].arrivalTime, ps[i].burstTime, ps[i].turnaroundTime, ps[i].waitingTime, ps[i].completionTime, ps[i].responseTime);
	}

	printf("\nAverage turnaround time: %f\n", avgTurnaroundTime/n);
	printf("Average waiting time: %f\n", avgWaitingTime/n);
	printf("Average response time: %f\n", avgResponseTime/n);

	return 0; 
}
