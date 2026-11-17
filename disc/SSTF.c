#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define INF LLONG_MAX

void sstf(int head, int n, int req[]) {
    int total = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    printf("Seek Sequence\n");
    printf("%d", head);
    for (int count = 0; count < n; count++) {
        long long min = INF;
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int diff = abs(head - req[i]);
                if (diff < min) {
                    min = diff;
                    minIndex = i;
                }
            }
        }
        visited[minIndex] = 1;
        total += min;
        head = req[minIndex];
        printf("->%d", head);
    }
    printf("\nTotal head movement = %d\n", total);
}

int main()
{
    int n, head;
    printf("Enter number of requests : ");
    scanf("%d", &n);
    int request[n];
    printf("Enter Request queue : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }
    printf("Enter initial head position : ");
    scanf("%d", &head);
    sstf(head, n, request);
return 0;
}