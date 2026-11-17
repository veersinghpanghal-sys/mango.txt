#include<stdio.h>

#define n 5

struct process {
    int pid;
    int at;
    int bt;
    int start;
    int ct;
    int tat;
    int wt;
    int completed;
};

struct process p[n] = {{1, 0, 8, 0, 0, 0, 0, 0}, {2, 1, 4, 0, 0, 0, 0, 0}, {3, 2, 2, 0, 0, 0, 0, 0}, {4, 3, 1, 0, 0, 0, 0, 0}, {5, 4, 3, 0, 0, 0, 0, 0}};

int currentTime = 0;

int findMax_rr() {
    int index = -1;
    float maxRR = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].completed == 0 && currentTime >= p[i].at) {
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
    while (count < 5) {
        int maxIndex = findMax_rr();
        if (maxIndex == -1) {
            currentTime++;
            continue;
        }

        p[maxIndex].start = currentTime;
        currentTime += p[maxIndex].bt;
        p[maxIndex].ct = currentTime;
        p[maxIndex].tat = p[maxIndex].ct - p[maxIndex].at;
        p[maxIndex].wt = p[maxIndex].tat - p[maxIndex].bt;
        p[maxIndex].completed = 1;
        count++;
    }
}

void printResult() {
    float totalTAT = 0, totalWT = 0;
    printf("PID\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    }
    printf("Average WT = %.2f | Average TAT = %.2f\n", totalWT / n, totalTAT / n);
}

int main()
{
    hrrn();
    printResult();
return 0;
}