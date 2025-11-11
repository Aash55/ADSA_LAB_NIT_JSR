#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a Job
typedef struct {
    int id;       // Job ID (1, 2, 3, ...)
    int deadline; // Deadline for the job
} Job;

// Comparison function for qsort to sort jobs by deadline in ascending order
int compareJobs(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    return jobA->deadline - jobB->deadline; // Ascending order by deadline
}

// Function to find the maximum deadline among all jobs
int findMaxDeadline(Job jobs[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > max) {
            max = jobs[i].deadline;
        }
    }
    return max;
}

// Function to implement the greedy job scheduling algorithm
void jobScheduling(Job jobs[], int n) {
    // 1. Sort the jobs by their deadline in ascending order
    qsort(jobs, n, sizeof(Job), compareJobs);

    // Find the maximum deadline to determine the required time slots
    int maxDeadline = findMaxDeadline(jobs, n);
    
    // An array to track which time slot is occupied. 
    // Size is maxDeadline + 1 (to use 1-based indexing for time slots 1 to maxDeadline)
    int *schedule = (int *)malloc((maxDeadline + 1) * sizeof(int));
    // Initialize all slots to 0 (meaning empty)
    for (int i = 0; i <= maxDeadline; i++) {
        schedule[i] = 0;
    }

    int scheduledJobsCount = 0;

    printf("Processing %d jobs (Max Deadline: %d). Unit time processing assumed.\n", n, maxDeadline);
    
    // 2. Iterate through all sorted jobs
    for (int i = 0; i < n; i++) {
        // 3. Try to schedule the current job (jobs[i]) in the latest possible time slot
        // that is less than or equal to its deadline (jobs[i].deadline).
        
        // Loop backwards from the deadline down to time slot 1
        for (int j = jobs[i].deadline; j >= 1; j--) {
            if (schedule[j] == 0) {
                // Slot 'j' is free. Schedule the job here.
                schedule[j] = jobs[i].id;
                scheduledJobsCount++;
                printf(" -> Job J%d scheduled at time slot %d (Deadline: %d)\n", jobs[i].id, j, jobs[i].deadline);
                break; // Job is scheduled, move to the next job
            }
        }
    }

    // 4. Print the final schedule
    printf("\n--- Final Maximum Schedule ---\n");
    printf("Total Jobs Scheduled: %d\n", scheduledJobsCount);
    
    printf("Time Slots (1 to %d): ", maxDeadline);
    for (int i = 1; i <= maxDeadline; i++) {
        if (schedule[i] != 0) {
            printf("| Slot %d: J%d ", i, schedule[i]);
        } else {
            printf("| Slot %d: -- ", i);
        }
    }
    printf("|\n");

    free(schedule);
}

// Main function
int main() {
    // Example Job Data: Only Deadline is relevant for this specific problem (unit time/max number of jobs)
    Job jobs[] = {
        {1, 2}, // Job 1, Deadline 2
        {2, 1}, // Job 2, Deadline 1
        {3, 2}, // Job 3, Deadline 2
        {4, 1}, // Job 4, Deadline 1
        {5, 3}  // Job 5, Deadline 3
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobScheduling(jobs, n);

    return 0;
}