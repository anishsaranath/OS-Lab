#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, hungry, pos[10], choice;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);
    printf("How many are hungry: ");
    scanf("%d", &hungry);

    for (int i = 0; i < hungry; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &pos[i]);
    }

    while (1) {
        printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Allow one philosopher to eat at any time\n");
            for (int i = 0; i < hungry; i++) {
                for (int j = 0; j < hungry; j++) {
                    printf("P %d is waiting\n", pos[j]);
                }
                printf("P %d is granted to eat\n", pos[i]);
                printf("P %d has finished eating\n", pos[i]);
            }
        } else if (choice == 2) {
            printf("Allow two philosophers to eat at any time\n");
            for (int i = 0; i < hungry; i++) {
                printf("P %d is waiting\n", pos[i]);
            }

            for (int i = 0; i < hungry; i += 2) {
                if (i + 1 < hungry) {
                    printf("P %d and P %d are granted to eat\n", pos[i], pos[i+1]);
                    printf("P %d and P %d have finished eating\n", pos[i], pos[i+1]);
                } else {
                    printf("P %d is granted to eat\n", pos[i]);
                    printf("P %d has finished eating\n", pos[i]);
                }
            }
        } else if (choice == 3) {
            exit(0);
        }
    }

    return 0;
}
