#include<stdio.h>
#include<stdlib.h>

void fcfs(int head, int n, int req[]) {
    int total = 0;
    printf("Seek Sequence\n");
    printf("%d", head);
    for (int i = 0; i < n; i++) {
        int movement = abs(head - req[i]);
        total += movement;
        head = req[i];
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
    fcfs(head, n, request);
return 0;
}