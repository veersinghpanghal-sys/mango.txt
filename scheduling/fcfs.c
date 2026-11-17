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
};

struct process p[n] = {{1, 0, 8, 0, 0, 0, 0}, {2, 1, 4, 0, 0, 0, 0}, {3, 2, 2, 0, 0, 0, 0}, {4, 3, 1, 0, 0, 0, 0}, {5, 4, 3, 0, 0, 0, 0}};


void fcfs() {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at )  {
            currentTime = p[i].at;
        }  
        p[i].start = currentTime;
        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        
    }
}

void printResult() {
    float totalTAT = 0, totalWT = 0;
    printf("PID\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += [i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    }
    printf("Average WT = %.2f | Average TAT = %.2f\n", totalWT / n, totalTAT / n);
}

int main()
{
    fcfs();
    printResult();
return 0;
}