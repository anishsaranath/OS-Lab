#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int available[m];
    int max[n][m];
    int allocation[n][m];
    int need[n][m];
    int i, j;

    printf("Enter available resources (instances of each type):\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    bool finish[n];
    int work[m];
    int safeSeq[n];
    int count = 0;

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
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is NOT in a safe state. Deadlock may occur.\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state.\nSafe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}
