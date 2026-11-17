#include<stdio.h>
#define MAX 100
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocated[MAX];
    int fragmentation[MAX];
    int remaining[MAX];
    for (int i = 0; i < m; i++) {
        remaining[i] = blockSize[i];
    }
    for (int i = 0; i < n; i++) {
        allocated[i] = -1;
        fragmentation[i] = 0;
        
        int best = -1;
        for (int j = 0; j < m; j++) {
            if (remaining[j] > processSize[i]) {
                if (best == -1 || remaining[j] < remaining[best]) {
                    best = j;
                }
            }
        }
        if (best != -1) {
            
        }
        
    }
    int total = 0;
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");
    for (int i = 0; i < n; i++) {
        if (allocated[i] == -1) {
            printf("%d\t\t%d\t\tNot Allocated\t-\n")
        }
        else {
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocated[i] + 1, fragmentation[i]);
        }
    }
}

int main()
{
    
return 0;
}