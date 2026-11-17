
#include <stdio.h>
#include <stdlib.h>

void scan(int head, int n, int req[], int diskSize) {

    int total = 0;

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    printf("\nSeek Sequence: %d", head);

    int pos = 0;

    while (pos < n && req[pos] < head) {
        pos++;
    }

    for (int i = pos; i < n; i++) {
        total += abs(req[i] - head);
        head = req[i];
        printf("->%d", head);
    }
    
    for (int i = pos - 1; i >= 0; i--) {
        total += abs(head - req[i]);
        head = req[i];
        printf("->%d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main() {

    int n, head, diskSize;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];

    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    scan(head, n, req, diskSize);

    return 0;
}
