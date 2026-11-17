
#include <stdio.h>

#define MAX 100

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int remaining[MAX];
    int fragmentation[MAX];

    for (int i = 0; i < m; i++)
        remaining[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        fragmentation[i] = 0;

        for (int j = 0; j < m; j++) {
            if (remaining[j] >= processSize[i]) {
                allocation[i] = j;
                fragmentation[i] = remaining[j] - processSize[i];
                remaining[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nMemory Allocation using First Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");

    int total = 0;

    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, fragmentation[i]);

            total += fragmentation[i];
        } else {
            printf("%d\t\t%d\t\tNot Allocated\t-\n", i + 1, processSize[i]);
        }
    }

    printf("Total Internal Fragmentation: %d\n", total);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int remaining[MAX];
    int fragmentation[MAX];

    for (int i = 0; i < m; i++)
        remaining[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        fragmentation[i] = 0;

        int best = -1;

        for (int j = 0; j < m; j++) {
            if (remaining[j] >= processSize[i]) {
                if (best == -1 || remaining[j] < remaining[best])
                    best = j;
            }
        }

        if (best != -1) {
            allocation[i] = best;
            fragmentation[i] = remaining[best] - processSize[i];
            remaining[best] -= processSize[i];
        }
    }

    printf("\nMemory Allocation using Best Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");

    int total = 0;

    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n",
                   i + 1, processSize[i],
                   allocation[i] + 1, fragmentation[i]);

            total += fragmentation[i];
        } else {
            printf("%d\t\t%d\t\tNot Allocated\t-\n",
                   i + 1, processSize[i]);
        }
    }

    printf("Total Internal Fragmentation: %d\n", total);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int remaining[MAX];
    int fragmentation[MAX];

    for (int i = 0; i < m; i++)
        remaining[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        fragmentation[i] = 0;

        int worst = -1;

        for (int j = 0; j < m; j++) {
            if (remaining[j] >= processSize[i]) {
                if (worst == -1 || remaining[j] > remaining[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            allocation[i] = worst;
            fragmentation[i] = remaining[worst] - processSize[i];
            remaining[worst] -= processSize[i];
        }
    }

    printf("\nMemory Allocation using Worst Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");

    int total = 0;

    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n",
                   i + 1, processSize[i],
                   allocation[i] + 1, fragmentation[i]);

            total += fragmentation[i];
        } else {
            printf("%d\t\t%d\t\tNot Allocated\t-\n",
                   i + 1, processSize[i]);
        }
    }

    printf("Total Internal Fragmentation: %d\n", total);
}

int main() {
    int m = 5;
    int n = 4;

    int blockSize[MAX] = {100, 500, 200, 300, 600};
    int processSize[MAX] = {212, 417, 112, 426};

    printf("Memory Blocks:\n");
    for (int i = 0; i < m; i++)
        printf("%d ", blockSize[i]);

    printf("\n\nProcess Sizes:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", processSize[i]);

    printf("\n");

    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);

    return 0;
}
