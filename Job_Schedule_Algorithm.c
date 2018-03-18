#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define JOB_LENGTH 7

#define SWAP(X, Y) { Job TEMP = (X); (X) = (Y); (Y) = TEMP; }

typedef struct _Job {
    int number;
    int deadline;
    int profit;
} Job;

int  Compare(const void *, const void *);
void Job_Schedule(int, Job *, Job *);
bool Is_Feasible_Sequence(Job *, int, int, Job *);

int main(void)
{
    Job deadline[] = {{1, 2, 40}, {2, 4, 15}, {3, 3, 60},
                      {4, 2, 20}, {5, 3, 10}, {6, 1, 45}, {7, 1, 55}};

    qsort(deadline, JOB_LENGTH, sizeof(*deadline), Compare);

    Job job[JOB_LENGTH] = {0};
    Job_Schedule(JOB_LENGTH, deadline, job);

    printf("Job   Deadline   Profit\n");
    for (int i = 0; job[i].number; i++) {
        printf(" %d       %d         %d\n", job[i].number, job[i].deadline, job[i].profit);
    }
    
    return 0;
}

int Compare(const void *numberA, const void *numberB)
{
    Job *jobA = (Job *) numberA;
    Job *jobB = (Job *) numberB;

    return jobB->profit - jobA->profit;
}

void Job_Schedule(int length, Job *deadline, Job *job)
{
    /* Because the profit was sorted in descending order,
    ** so the first element of job is the highest profit. */

    Job temp[JOB_LENGTH] = {0};
    
    job[0] = temp[0] = deadline[0];    
    for (int i = 1, index = 1; i < length; i++) {
        temp[index] = deadline[i];
        
        if (Is_Feasible_Sequence(temp, 0, index + 1, deadline)) {
            memcpy(job, temp, (index + 1) * sizeof(*job));
            index++;
        }
    }
}

/* Listing all permutation of job, and check if the job is feasible or not. */
bool Is_Feasible_Sequence(Job *job, int start, int end, Job *deadline)
{
    if (start == end) {
        int i;
        for (i = 0; i < end; i++) {
            if (job[i].deadline < i + 1)
                break;
        }

        if (i == end) return true;
    } else {
        for (int i = start; i < end; i++) {
            SWAP(job[start], job[i]);
            if (Is_Feasible_Sequence(job, start + 1, end, deadline)) return true;
            SWAP(job[start], job[i]);
        }
    }

    return false;
}
