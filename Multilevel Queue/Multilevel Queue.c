#include <stdio.h>

#define MAX 100

int main() {
    int n, i, j;

    int PID[MAX], AT[MAX], BT[MAX], TYPE[MAX];
    int CT[MAX], TAT[MAX], WT[MAX], Start[MAX];

    int systemQueue[MAX], userQueue[MAX];
    int sysCount = 0, userCount = 0;

    int time = 0, temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &PID[i]);
        printf("Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Burst Time: ");
        scanf("%d", &BT[i]);
        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &TYPE[i]);
    }


    for(i = 0; i < n; i++) {
        if(TYPE[i] == 0)
            systemQueue[sysCount++] = i;
        else
            userQueue[userCount++] = i;
    }


    for(i = 0; i < sysCount - 1; i++) {
        for(j = i + 1; j < sysCount; j++) {
            if(AT[systemQueue[i]] > AT[systemQueue[j]]) {
                temp = systemQueue[i];
                systemQueue[i] = systemQueue[j];
                systemQueue[j] = temp;
            }
        }
    }


    for(i = 0; i < userCount - 1; i++) {
        for(j = i + 1; j < userCount; j++) {
            if(AT[userQueue[i]] > AT[userQueue[j]]) {
                temp = userQueue[i];
                userQueue[i] = userQueue[j];
                userQueue[j] = temp;
            }
        }
    }


    for(i = 0; i < sysCount; i++) {
        int p = systemQueue[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }


    for(i = 0; i < userCount; i++) {
        int p = userQueue[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }


    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            PID[i], AT[i], BT[i], TYPE[i],
            CT[i], TAT[i], WT[i]);
    }

    return 0;
}
