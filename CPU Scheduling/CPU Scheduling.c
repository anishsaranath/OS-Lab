#include <stdio.h>
#include <stdlib.h>

void rate_monotonic(int ids[], int periods[], int exec_times[], int n, int time) {
    int remaining[10], next_release[10];
    int current_time = 0, completed_jobs = 0;

    for (int i = 0; i < n; i++) {
        remaining[i] = exec_times[i];
        next_release[i] = 0;
    }

    printf("\nRate Monotonic Scheduling\n");

    while (current_time < time) {
        int selected = -1;
        int min_period = 999999;
        for (int i = 0; i < n; i++) {
            if (next_release[i] <= current_time && remaining[i] > 0) {
                if (periods[i] < min_period) {
                    min_period = periods[i];
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", current_time, ids[selected]);
            remaining[selected]--;

            if (remaining[selected] == 0) {
                next_release[selected] += periods[selected];
                remaining[selected] = exec_times[selected];
                completed_jobs++;
            }
        } else {
            printf("Time %d: Idle\n", current_time);
        }

        current_time++;
    }
}

void earliest_deadline_first(int ids[], int periods[], int exec_times[], int deadlines[], int n, int time) {
    int remaining[10], next_release[10];
    int current_time = 0, completed_jobs = 0;

    for (int i = 0; i < n; i++) {
        remaining[i] = exec_times[i];
        next_release[i] = 0;
    }

    printf("\nEarliest Deadline First Scheduling\n");

    while (current_time < time) {
        int selected = -1;
        int min_deadline = 999999;

        for (int i = 0; i < n; i++) {
            if (next_release[i] <= current_time && remaining[i] > 0) {
                int absolute_deadline = next_release[i] + deadlines[i];
                if (absolute_deadline < min_deadline) {
                    min_deadline = absolute_deadline;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", current_time, ids[selected]);
            remaining[selected]--;

            if (remaining[selected] == 0) {
                next_release[selected] += periods[selected];
                remaining[selected] = exec_times[selected];
                completed_jobs++;
            }
        } else {
            printf("Time %d: Idle\n", current_time);
        }

        current_time++;
    }
}

void proportional_scheduling(int ids[], int weights[], int n, int time) {
    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        total_weight += weights[i];
    }
    int slots[100] = {0};
    int *share = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        share[i] = (weights[i] * time + total_weight / 2) / total_weight;
    }
    int current_time = 0;
    int done = 0;

    while (!done) {
        done = 1;
        for (int i = 0; i < n && current_time < time; i++) {
            if (share[i] > 0) {
                slots[current_time++] = ids[i];
                share[i]--;
                done = 0;
            }
        }
    }
    while (current_time < time) {
        slots[current_time++] = -1;
    }

    printf("\nProportional Scheduling\n");
    for (int i = 0; i < time; i++) {
        if (slots[i] != -1) {
            printf("Time %d: Task %d\n", i, slots[i]);
        } else {
            printf("Time %d: Idle\n", i);
        }
    }

    free(share);
}

int main() {
    int ids[10], periods[10], exec_times[10], deadlines[10], weights[10];
    int n, time;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    printf("Enter simulation time: ");
    scanf("%d", &time);

    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        printf("\nTask %d:\n", i+1);
        printf("  Period: ");
        scanf("%d", &periods[i]);
        printf("  Execution time: ");
        scanf("%d", &exec_times[i]);
        printf("  Deadline: ");
        scanf("%d", &deadlines[i]);
        printf("  Weight: ");
        scanf("%d", &weights[i]);
    }

    rate_monotonic(ids, periods, exec_times, n, time);
    earliest_deadline_first(ids, periods, exec_times, deadlines, n, time);
    proportional_scheduling(ids, weights, n, time);

    return 0;
}
