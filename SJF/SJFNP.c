#include <stdio.h>

int main() {
    int n, bt[10], bt_copy[10], wt[10], tat[10], at[10], ct[10], p[10];
    int i, j, time = 0, completed = 0, smallest;
    float avg_wt = 0, avg_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Process %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        bt_copy[i] = bt[i];
    }
    while(completed < n) {
        smallest = -1;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && bt[i] > 0) {
                if(smallest == -1 || bt[i] < bt[smallest]) {
                    smallest = i;
                }
            }
        }
        if(smallest == -1) {
            time++;
            continue;
        }
        time += bt[smallest];
        ct[smallest] = time;
        tat[smallest] = ct[smallest] - at[smallest];
        wt[smallest] = tat[smallest] - bt[smallest];

        bt[smallest] = 0;
        completed++;
    }

    printf("\nP\tAT\tBT\tCT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt_copy[i], ct[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
