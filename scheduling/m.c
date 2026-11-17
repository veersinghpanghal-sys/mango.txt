#include<stdio.h>

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
    int start;
    int response;
    int completed;
};

struct process p[n] = {
    {1, 0, 8, 8, 0, 0, 0, -1, 0, 0}, 
    {2, 1, 4, 4, 0, 0, 0, -1, 0, 0}, 
    {3, 2, 2, 2, 0, 0, 0, -1, 0, 0}, 
    {4, 3, 1, 1, 0, 0, 0, -1, 0, 0},
    {5, 4, 3, 3, 0, 0, 0, -1, 0, 0}
};


void srtf() {
    int currentTime = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].start = currentTime;
        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

}

void print() {
    float totalTAT = 0, totalWT = 0, totalRT = 0;
    printf("PID\tAT\tBT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        totalRT += p[i].response;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, p[i].at, p[i].bt, p[i].tat, p[i].wt, p[i].response);
    }
    printf("TotalTAT : %.2f | TotalWT : %.2f | TotalRT : %.2f |", totalTAT / n, totalWT / n, totalRT / n);
}

int main()
{
    srtf();
    print();
return 0;
}