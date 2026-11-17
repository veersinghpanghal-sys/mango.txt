#include<stdio.h>
#include<stdlib.h>

#define n 5
#define tq 2

struct process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
    int response;
    int start;
    int completed;
};

struct process p[n] = {
    {1, 0, 8, 8, 0, 0, 0, 0, -1, 0},
    {2, 1, 4, 4, 0, 0, 0, 0, -1, 0},
    {3, 2, 2, 2, 0, 0, 0, 0, -1, 0},
    {4, 3, 1, 1, 0, 0, 0, 0, -1, 0},
    {5, 4, 3, 3, 0, 0, 0, 0, -1, 0}
};

void rr() {
    int queue[100];
    int front = 0, rear = 0;
    int added[n] = {0};

    int currentTime = 0;
    int count = 0;

    while (count < n) {

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && added[i] == 0) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (front == rear) {
            currentTime++;
            continue;
        }

        int i = queue[front++];

        if (p[i].start == -1)
            p[i].start = currentTime;

        int time;

        if (p[i].rt < tq)
            time = p[i].rt;
        else
            time = tq;

        currentTime += time;
        p[i].rt -= time;

        for (int j = 0; j < n; j++) {
            if (p[j].at <= currentTime && added[j] == 0) {
                queue[rear++] = j;
                added[j] = 1;
            }
        }

        if (p[i].rt == 0) {
            p[i].ct = currentTime;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            p[i].response = p[i].start - p[i].at;
            p[i].completed = 1;
            count++;
        }
        else {
            queue[rear++] = i;
        }
    }
}

void printResult() {
    float totalTAT = 0;
    float totalWT = 0;
    float totalRT = 0;

    printf("PID\tAT\tBT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        totalRT += p[i].response;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].tat,
               p[i].wt,
               p[i].response);
    }

    printf("\nAverage WT = %.2f | Average TAT = %.2f | Average RT = %.2f\n",
           totalWT / n,
           totalTAT / n,
           totalRT / n);
}

int main() {
    rr();
    printResult();

    return 0;
}