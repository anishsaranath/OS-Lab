#include <stdio.h>

int main() {
    int n, bt[10], bt_copy[10], wt[10], tat[10], at[10], ct[10], p[10], pr[10];
    int i, j, time = 0, completed = 0, highest;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("\nProcess %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &pr[i]);
        bt_copy[i] = bt[i];
    }

    printf("\nGantt Chart: ");

    while(completed < n) {
        highest = -1;
        int max_pr = 9999;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && bt[i] > 0 && pr[i] < max_pr) {
                max_pr = pr[i];
                highest = i;
            }
        }

        if(highest == -1) {
            time++;
            continue;
        }

        printf("P%d ", p[highest]);
        time += bt[highest];
        ct[highest] = time;
        tat[highest] = ct[highest] - at[highest];
        wt[highest] = tat[highest] - bt[highest];

        bt[highest] = 0;
        completed++;
    }

    printf("\n\nP\tAT\tBT\tPR\tCT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt_copy[i], pr[i], ct[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
