#include <stdio.h>
#include <string.h>

#define n 5

void printResult(char name[], char pid[][3], int at[], int bt[],
                 int ct[], int start[]) {

    int tat[n], wt[n], rt[n];
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    printf("\n%s\n", name);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = start[i] - at[i];

        totalTAT += tat[i];
        totalWT += wt[i];
        totalRT += rt[i];

        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i],
               tat[i], wt[i], rt[i]);
    }

    printf("Average WT = %.2f | Average TAT = %.2f | Average RT = %.2f\n",
           totalWT / n, totalTAT / n, totalRT / n);
}

void fcfs(char pid[][3], int at[], int bt[]) {

    int ct[n], start[n];
    int currentTime = 0;

    for (int i = 0; i < n; i++) {

        if (currentTime < at[i])
            currentTime = at[i];

        start[i] = currentTime;
        currentTime += bt[i];
        ct[i] = currentTime;
    }

    printResult("FCFS", pid, at, bt, ct, start);
}

void sjf(char pid[][3], int at[], int bt[]) {

    int ct[n] = {0};
    int start[n] = {0};
    int completed[n] = {0};

    int currentTime = 0;
    int count = 0;

    while (count < n) {

        int shortest = -1;

        for (int i = 0; i < n; i++) {

            if (completed[i] == 0 && at[i] <= currentTime) {

                if (shortest == -1 ||
                    bt[i] < bt[shortest]) {

                    shortest = i;
                }
            }
        }

        if (shortest == -1) {

            currentTime++;

            continue;
        }

        start[shortest] = currentTime;

        currentTime += bt[shortest];

        ct[shortest] = currentTime;

        completed[shortest] = 1;

        count++;
    }

    printResult("Non-Preemptive SJF", pid, at, bt, ct, start);
}

void srtf(char pid[][3], int at[], int bt[]) {

    int remaining[n];
    int ct[n] = {0};
    int start[n];

    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
        start[i] = -1;
    }

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {

        int shortest = -1;

        for (int i = 0; i < n; i++) {

            if (at[i] <= currentTime && remaining[i] > 0) {

                if (shortest == -1 ||
                    remaining[i] < remaining[shortest]) {

                    shortest = i;
                }
            }
        }

        if (shortest == -1) {

            currentTime++;

            continue;
        }

        if (start[shortest] == -1)
            start[shortest] = currentTime;

        remaining[shortest]--;

        currentTime++;

        if (remaining[shortest] == 0) {

            ct[shortest] = currentTime;

            completed++;
        }
    }

    printResult("Preemptive SJF (SRTF)", pid, at, bt, ct, start);
}

int main() {

    char pid[n][3] = {"P1", "P2", "P3", "P4", "P5"};

    int at[n] = {0, 1, 2, 3, 4};

    int bt[n] = {8, 4, 2, 1, 3};

    fcfs(pid, at, bt);

    sjf(pid, at, bt);

    srtf(pid, at, bt);

    return 0;
}