#include <stdio.h>

void run(int ref[], int n, int nf, int mode) {
    int frames[10], matrix[10][50], tracker[10] = {0}, fifo_idx = 0, faults = 0;
    for (int i = 0; i < nf; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = -1;
        for (int j = 0; j < nf; j++) if (frames[j] == ref[i]) found = j;

        if (found != -1) {
            if (mode == 2) tracker[found] = i;
        } else {
            faults++;
            int slot = -1;
            for (int j = 0; j < nf; j++) if (frames[j] == -1) { slot = j; break; }

            if (slot == -1) {
                if (mode == 1) { slot = fifo_idx; fifo_idx = (fifo_idx + 1) % nf; }
                else {
                    int opt_idx[10];
                    for (int j = 0; j < nf; j++) {
                        opt_idx[j] = 1e9;
                        for (int k = i + 1; k < n; k++) if (frames[j] == ref[k]) { opt_idx[j] = k; break; }
                    }
                    int target = 0;
                    for (int j = 1; j < nf; j++) {
                        if (mode == 2 && tracker[j] < tracker[target]) target = j;
                        if (mode == 3 && opt_idx[j] > opt_idx[target]) target = j;
                    }
                    slot = target;
                }
            }
            frames[slot] = ref[i];
            if (mode == 2) tracker[slot] = i;
        }
        for (int j = 0; j < nf; j++) matrix[j][i] = frames[j];
    }

    for (int i = 0; i < nf; i++) {
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != -1) printf("%d\t", matrix[i][j]); else printf(" \t");
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int n, nf, ref[50];
    printf("Enter number of pages: "); scanf("%d", &n);
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);
    printf("Enter number of frames: "); scanf("%d", &nf);

    printf("\n--- FIFO PAGE REPLACEMENT ---\n"); run(ref, n, nf, 1);
    printf("\n--- LRU PAGE REPLACEMENT ---\n");  run(ref, n, nf, 2);
    printf("\n--- OPTIMAL PAGE REPLACEMENT ---\n"); run(ref, n, nf, 3);
    return 0;
}
