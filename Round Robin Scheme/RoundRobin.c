#include <stdio.h>

int main() {
    int n, quantum, i, time = 0, remain, flag = 0;
    int bt[10], at[10], wt[10], tat[10], rt[10], ct[10];
    int total_wt = 0, total_tat = 0;
    int gantt[100], gantt_time[100], gc_index = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);
    remain = n;

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; remain != 0;) {
        if(at[i] <= time && rt[i] > 0) {
            if(rt[i] <= quantum) {
                time += rt[i];
                rt[i] = 0;
                remain--;
                ct[i] = time;
                tat[i] = ct[i] - at[i];
                wt[i] = tat[i] - bt[i];
                total_wt += wt[i];
                total_tat += tat[i];
                printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);

                gantt[gc_index] = i+1;
                gantt_time[gc_index] = time;
                gc_index++;
                flag = 1;
            } else {
                rt[i] -= quantum;
                time += quantum;
                gantt[gc_index] = i+1;
                gantt_time[gc_index] = time;
                gc_index++;
                flag = 1;
            }
        }

        i++;
        if(i == n) {
            if(flag == 0) {
                time++;
            }
            i = 0;
            flag = 0;
        }
    }
    printf("\nGantt Chart:\n|");
    for(i = 0; i < gc_index; i++) {
        printf(" P%d |", gantt[i]);
    }
    printf("\n0");
    for(i = 0; i < gc_index; i++) {
        printf("   %d", gantt_time[i]);}
    printf("\n\nAverage Turnaround Time = %.2f", (float)total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt/n);
    return 0;
}
