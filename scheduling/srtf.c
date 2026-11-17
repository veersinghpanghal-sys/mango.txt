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
    int start;
    int completed;
};

struct process p[n] = { {1, 0, 8, 8, 0, 0, 0, -1, 0}, {2, 1, 4, 4, 0, 0, 0, -1, 0}, {3, 2, 2, 2, 0, 0, 0, -1, 0}, {4, 3, 1, 1, 0, 0, 0, -1, 0}, {5, 4, 3, 3, 0, 0, 0, -1, 0}
};

void srtf () {
    int count = 0;
    int currentTime = 0;
    while (count < 5) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].rt > 0) {
                if (shortest == -1 || p[i].rt < p[shortest].rt)
                    shortest = i;
            }
        }
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        if (p[shortest].start == -1) p[shortest].start = currentTime;
        
        p[shortest].rt--;
        currentTime++;


        if (p[shortest].rt == 0) {
            p[shortest].ct = currentTime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            p[shortest].completed = 1;
            count++;
        }
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
    srtf();
    printResult();
return 0;
}