#include <stdio.h>

#define n 5
#define quantum 3

struct process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int responseTime;
};

struct process p[n] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 2}, {4, 3, 1}, {5, 4, 3}};

int remainingBT[n] = {8, 4, 2, 1, 3};
int visited[n] = {0};

int queue[100];
int front = 0;
int rear = 0;

int currentTime = 0;

void enqueue(int index) {
    queue[rear] = index;
    rear++;
}

int dequeue() {
    int index = queue[front];
    front++;
    return index;
}

void roundRobin() {
    int completed = 0;
    int firstStart[n];

    for (int i = 0; i < n; i++)
        firstStart[i] = -1;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }

        if (front == rear) {
            currentTime++;
            continue;
        }

        int index = dequeue();

        if (firstStart[index] == -1) {
            firstStart[index] = currentTime;

            p[index].responseTime =
                currentTime - p[index].at;
        }

        if (remainingBT[index] > quantum) {
            currentTime += quantum;
            remainingBT[index] -= quantum;
        }
        else {
            currentTime += remainingBT[index];
            remainingBT[index] = 0;

            p[index].ct = currentTime;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }

        if (remainingBT[index] > 0) {
            enqueue(index);
        }
    }
}

int main() {
    roundRobin();

    printf("Round Robin (Time Quantum = %d)\n\n", quantum);

    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    float totalTAT = 0;
    float totalWT = 0;
    float totalRT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt,
               p[i].responseTime);

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        totalRT += p[i].responseTime;
    }

    printf("\nAverage TAT = %.2f\n", totalTAT / n);
    printf("Average WT  = %.2f\n", totalWT / n);
    printf("Average RT  = %.2f\n", totalRT / n);

    return 0;
}