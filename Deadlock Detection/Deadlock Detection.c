#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int available[m], allocation[n][m], request[n][m];
    int i, j;

    printf("Enter available resources: ");
    for (i = 0; i < m; i++) scanf("%d", &available[i]);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Request matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    bool finish[n];
    int work[m], safeSeq[n], count = 0;

    for (i = 0; i < n; i++) {
        finish[i] = false;
    }

    for (i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < m; j++) work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                    printf("P%d is visited(%d%d%d)\n", i, work[0], work[1], work[2]);
                }
            }
        }
        if (!found) {
            printf("\nSYSTEM IS IN DEADLOCK\n");
            printf("Processes causing deadlock: ");
            for (int k = 0; k < n; k++) {
                if (!finish[k]) printf("P%d ", k);
            }
            printf("\n");
            return 0;
        }
    }

    printf("\nSYSTEM IS NOT IN DEADLOCK\n");
    printf("The Safe Sequence is (");
    for (i = 0; i < n; i++) printf("P%d%s", safeSeq[i], (i == n - 1) ? "" : " ");
    printf(")\n");

    return 0;
}
