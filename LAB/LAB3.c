#include<stdio.h>
#include<string.h>

struct process {
    char name[3];
    int completion_time;
    int tat_time;
    int waiting_time;
};

struct process queue[5];

int front = -1, rear = -1;

void insertQueue(struct process p, int n) {
    if (rear == n - 1) return;
    else if (front == -1) front = rear = 0;
    else rear++;

    queue[rear] = p;
}

struct process deleteQueue() {
    struct process p = queue[front];

    if (rear == front)
        front = rear = -1;
    else
        front++;

    return p;
}

int main()
{
    int serviceTime[5] = {3, 3, 5, 2, 3};
    int arrivalTime[5] = {0, 2, 3, 4, 8};

    struct process p[5] = {
        {"P1", 0, 0, 0},
        {"P2", 0, 0, 0},
        {"P3", 0, 0, 0},
        {"P4", 0, 0, 0},
        {"P5", 0, 0, 0}
    };

    int visited[5] = {0};
    int currentTime = 0;
    int completed = 0;

    float totalTAT = 0;
    float totalWT = 0;

    while (completed < 5) {

        for (int i = 0; i < 5; i++) {

            if ((arrivalTime[i] <= currentTime) && visited[i] == 0) {

                insertQueue(p[i], 5);
                visited[i] = 1;
            }
        }

        if (front == -1) {

            for (int i = 0; i < 5; i++) {

                if (visited[i] == 0) {
                    currentTime = arrivalTime[i];
                    break;
                }
            }

            continue;
        }

        struct process current = deleteQueue();

        int index = -1;

        for (int i = 0; i < 5; i++) {

            if (strcmp(p[i].name, current.name) == 0) {
                index = i;
                break;
            }
        }

        currentTime += serviceTime[index];

        p[index].completion_time = currentTime;

        p[index].tat_time =
            p[index].completion_time - arrivalTime[index];

        p[index].waiting_time =
            p[index].tat_time - serviceTime[index];

        totalTAT += p[index].tat_time;
        totalWT += p[index].waiting_time;

        completed++;
    }

    printf("First Come First Serve(FCFS) Non-Preemptive\n");

    printf("Process\tAT\tST\tCT\tTAT\tWT\n");

    for (int i = 0; i < 5; i++) {

        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name,
               arrivalTime[i],
               serviceTime[i],
               p[i].completion_time,
               p[i].tat_time,
               p[i].waiting_time);
    }

    printf("Average Turn Around Time : %.2f\n", totalTAT / 5);

    printf("Average Waiting Time : %.2f\n", totalWT / 5);

    return 0;
}