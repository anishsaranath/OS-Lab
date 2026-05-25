#include <stdio.h>

void simulate(int b[], int n, int p[], int m, int type) {
    int alloc[20], occupied[20] = {0};
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int idx = -1;
        for (int j = 0; j < n; j++) {
            if (!occupied[j] && b[j] >= p[i]) {
                if (type == 1) {
                    idx = j;
                    break;
                } else if (type == 2) {
                    if (idx == -1 || b[j] < b[idx]) idx = j;
                } else if (type == 3) {
                    if (idx == -1 || b[j] > b[idx]) idx = j;
                }
            }
        }
        if (idx != -1) {
            alloc[i] = idx;
            occupied[idx] = 1;
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, p[i]);
        if (alloc[i] != -1) printf("%d\n", alloc[i] + 1);
        else printf("Not Allocated\n");
    }
}

int main() {
    int b[20], p[20], b_bak[20], n, m;

    printf("Enter number of blocks: ");
    scanf("%d", &n);
    printf("Enter size of each block:\n");
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

    printf("Enter number of processes: ");
    scanf("%d", &m);
    printf("Enter size of each process:\n");
    for (int i = 0; i < m; i++) scanf("%d", &p[i]);

    for (int i = 0; i < n; i++) b_bak[i] = b[i];
    printf("\n--- FIRST FIT ALLOCATION ---");
    simulate(b_bak, n, p, m, 1);

    for (int i = 0; i < n; i++) b_bak[i] = b[i];
    printf("\n--- BEST FIT ALLOCATION ---");
    simulate(b_bak, n, p, m, 2);

    for (int i = 0; i < n; i++) b_bak[i] = b[i];
    printf("\n--- WORST FIT ALLOCATION ---");
    simulate(b_bak, n, p, m, 3);

    return 0;
}
