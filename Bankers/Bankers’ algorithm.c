#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int available[m], max[n][m], allocation[n][m], need[n][m];
    int i, j;

    printf("Enter available resources: ");
    for (i = 0; i < m; i++) scanf("%d", &available[i]);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int pid;
    printf("\nEnter process ID making a request (e.g., 1): ");
    scanf("%d", &pid);

    int request[m];
    printf("Enter Request for resources: ");
    for (j = 0; j < m; j++) scanf("%d", &request[j]);
    bool possible = true;
    for (j = 0; j < m; j++) {
        if (request[j] > need[pid][j] || request[j] > available[j]) {
            possible = false;
            break;
        }
    }

    if (possible) {
        for (j = 0; j < m; j++) {
            available[j] -= request[j];
            allocation[pid][j] += request[j];
            need[pid][j] -= request[j];
        }
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    bool finish[n];
    int work[m], safeSeq[n], count = 0;

    for (i = 0; i < n; i++) finish[i] = false;
    for (i = 0; i < m; i++) work[i] = available[i];

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < m; j++) work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                    printf("P%d is visited(%d%d%d)\n", i, work[0], work[1], work[2]); // Matches [cite: 5-9]
                }
            }
        }
        if (!found) {
            printf("\nSYSTEM IS NOT IN A SAFE STATE\n");
            return 0;
        }
    }

    printf("\nSYSTEM IS IN SAFE STATE [cite: 10]\n");
    printf("The Safe Sequence is (");
    for (i = 0; i < n; i++) printf("P%d%s", safeSeq[i], (i == n - 1) ? "" : " ");
    printf(") \n");

    return 0;
}
