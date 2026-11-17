#include<stdio.h>
#include<string.h>

#define n 5

struct process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};

struct process p[n] = {{1, 0, 8, 0, 0, 0, 0}, {2, 1, 4, 0, 0, 0, 0}, {3, 2, 2, 0, 0, 0, 0}, {4, 3, 1, 0, 0, 0, 0}, {5, 4, 3, 0, 0, 0, 0}
};

int currentTime = 0;
int completed[n] = {0};
float rr[n];

int findMax_rr() {
    int index = -1;
    float maxRR = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= currentTime && completed[i] == 0) {
            float waitingTime = currentTime - p[i].at;
            float rr = (float)(waitingTime + p[i].bt) / p[i].bt;
            if (rr > maxRR) {
                maxRR = rr;
                index = i;
            }
        }
    }
    return index;
}

void hrrn() {

    int count = 0;
    int start[n];

    while (count < n) {

        int maxRR_index = findMax_rr();

        if (maxRR_index == -1) {
            currentTime++;
            continue;
        }

        start[maxRR_index] = currentTime;

        p[maxRR_index].rt = start[maxRR_index] - p[maxRR_index].at;
        currentTime += p[maxRR_index].bt;
        p[maxRR_index].ct = currentTime;
        p[maxRR_index].tat = p[maxRR_index].ct - p[maxRR_index].at;
        p[maxRR_index].wt = p[maxRR_index].tat - p[maxRR_index].bt;
        completed[maxRR_index] = 1;
        count++;
    }
}

int main()
{
    hrrn();

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    int totaltat = 0;
    int totalwt = 0;
    int totalrt = 0;

    for (int i = 0; i < n; i++) {

        totaltat += p[i].tat;
        totalwt += p[i].wt;
        totalrt += p[i].rt;
    }

    float avgtat = (float)totaltat / n;
    float avgwt = (float)totalwt / n;
    float avgrt = (float)totalrt / n;

    printf("\nAverage TurnAround Time : %.2f\n", avgtat);
    printf("Average Waiting Time : %.2f\n", avgwt);
    printf("Average Response Time : %.2f\n", avgrt);

    return 0;
}