
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REQUESTS 10000

enum {
    FCFS = 1,
    SSTF,
    SCAN,
    CSCAN,
    LOOK,
    CLOOK
};

void sortRequests(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void addPosition(int path[], int *count, int position, int *movement) {
    *movement += abs(path[*count - 1] - position);
    path[(*count)++] = position;
}

void displayPath(int path[], int count) {
    printf("Seek Sequence: ");
    for (int i = 0; i < count; i++) {
        printf("%d", path[i]);
        if (i != count - 1)
            printf(" -> ");
    }

    printf("\n");
}

int runAlgorithm(int algorithm, int requests[], int n, int head, int diskSize, int direction, int display, double *executionTime) {
    int *arr = (int *)malloc(n * sizeof(int));
    int *path = (int *)malloc((n + 5) * sizeof(int));
    int *visited = (int *)calloc(n, sizeof(int));
    if (arr == NULL || path == NULL || visited == NULL) {
        printf("Memory allocation failed!\n");
        free(arr);
        free(path);
        free(visited);
        return -1;
    }

    for (int i = 0; i < n; i++)
        arr[i] = requests[i];

    sortRequests(arr, n);

    int count = 1;
    int movement = 0;

    path[0] = head;

    clock_t start = clock();

    if (algorithm == FCFS) {
        for (int i = 0; i < n; i++) {
            addPosition(path, &count, requests[i], &movement);
        }
    }

    else if (algorithm == SSTF) {
        int current = head;

        for (int i = 0; i < n; i++) {
            int minDistance = 2147483647;
            int selected = -1;

            for (int j = 0; j < n; j++) {
                if (!visited[j]) {
                    int distance = abs(current - requests[j]);

                    if (distance < minDistance) {
                        minDistance = distance;
                        selected = j;
                    }
                }
            }

            visited[selected] = 1;

            addPosition(path, &count, requests[selected], &movement);

            current = requests[selected];
        }
    }

    else if (algorithm == SCAN) {
        int split = 0;

        while (split < n && arr[split] < head)
            split++;

        if (direction == 1) {
            for (int i = split; i < n; i++)
                addPosition(path, &count, arr[i], &movement);

            if (split > 0) {
                addPosition(path, &count, diskSize - 1, &movement);

                for (int i = split - 1; i >= 0; i--)
                    addPosition(path, &count, arr[i], &movement);
            }
        }
        else {
            for (int i = split - 1; i >= 0; i--)
                addPosition(path, &count, arr[i], &movement);

            if (split < n) {
                addPosition(path, &count, 0, &movement);

                for (int i = split; i < n; i++)
                    addPosition(path, &count, arr[i], &movement);
            }
        }
    }

    else if (algorithm == CSCAN) {
        int split = 0;

        while (split < n && arr[split] < head)
            split++;

        if (direction == 1) {
            for (int i = split; i < n; i++)
                addPosition(path, &count, arr[i], &movement);

            if (split > 0) {
                addPosition(path, &count, diskSize - 1, &movement);
                addPosition(path, &count, 0, &movement);

                for (int i = 0; i < split; i++)
                    addPosition(path, &count, arr[i], &movement);
            }
        }
        else {
            for (int i = split - 1; i >= 0; i--)
                addPosition(path, &count, arr[i], &movement);

            if (split < n) {
                addPosition(path, &count, 0, &movement);
                addPosition(path, &count, diskSize - 1, &movement);

                for (int i = n - 1; i >= split; i--)
                    addPosition(path, &count, arr[i], &movement);
            }
        }
    }

    else if (algorithm == LOOK) {
        int split = 0;

        while (split < n && arr[split] < head)
            split++;

        if (direction == 1) {
            for (int i = split; i < n; i++)
                addPosition(path, &count, arr[i], &movement);

            for (int i = split - 1; i >= 0; i--)
                addPosition(path, &count, arr[i], &movement);
        }
        else {
            for (int i = split - 1; i >= 0; i--)
                addPosition(path, &count, arr[i], &movement);

            for (int i = split; i < n; i++)
                addPosition(path, &count, arr[i], &movement);
        }
    }

    else if (algorithm == CLOOK) {
        int split = 0;

        while (split < n && arr[split] < head)
            split++;

        if (direction == 1) {
            for (int i = split; i < n; i++)
                addPosition(path, &count, arr[i], &movement);

            for (int i = 0; i < split; i++)
                addPosition(path, &count, arr[i], &movement);
        }
        else {
            for (int i = split - 1; i >= 0; i--)
                addPosition(path, &count, arr[i], &movement);

            for (int i = n - 1; i >= split; i--)
                addPosition(path, &count, arr[i], &movement);
        }
    }

    clock_t end = clock();

    *executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    if (display) {
        displayPath(path, count);

        printf("Total Head Movement: %d cylinders\n", movement);

        printf("Execution Time: %.6f seconds\n",
               *executionTime);
    }

    free(arr);
    free(path);
    free(visited);

    return movement;
}

void performanceAnalysis() {
    int sizes[] = {100, 500, 1000, 2000, 5000};
    int diskSize = 100000;
    int head = 50000;
    int direction = 1;

    const char *names[] = {"FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK"};

    int *requests = (int *)malloc(MAX_REQUESTS * sizeof(int));

    if (requests == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    srand(42);

    printf("\n\t\t\t PERFORMANCE ANALYSIS \n");
    printf("Disk Size: %d cylinders\n", diskSize);
    printf("Initial Head: %d\n", head);
    printf("Direction: Right\n\n");

    printf("%-12s %-12s %-22s %-20s\n", "Algorithm", "Requests", "Head Movement", "Execution Time (sec)");

    for (int k = 0; k < 5; k++) {
        int n = sizes[k];

        for (int i = 0; i < n; i++)
            requests[i] = rand() % diskSize;

        for (int alg = FCFS; alg <= CLOOK; alg++) {
            double timeTaken;

            int movement = runAlgorithm(
                alg, requests, n, head,
                diskSize, direction, 0, &timeTaken
            );

            printf("%-12s %-12d %-22d %-20.6f\n", names[alg - 1], n, movement, timeTaken);
        }

        printf("\n");
    }

    free(requests);
}

int main() {
    int n, head, diskSize, direction;
    int choice;

    printf("DISK SCHEDULING ALGORITHMS\n");

    printf("1. FCFS\n");
    printf("2. SSTF\n");
    printf("3. SCAN\n");
    printf("4. C-SCAN\n");
    printf("5. LOOK\n");
    printf("6. C-LOOK\n");
    printf("7. Compare All Algorithms\n");
    printf("8. Performance Analysis\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 8) {
        performanceAnalysis();
        return 0;
    }

    if (choice < 1 || choice > 7) {
        printf("Invalid choice!\n");
        return 0;
    }

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_REQUESTS) {
        printf("Invalid number of requests!\n");
        return 0;
    }

    int *requests = (int *)malloc(n * sizeof(int));

    if (requests == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    printf("Enter the request sequence: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the total number of cylinders: ");
    scanf("%d", &diskSize);

    if (diskSize <= 0 || head < 0 || head >= diskSize) {
        printf("Invalid disk size or head position!\n");
        free(requests);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (requests[i] < 0 || requests[i] >= diskSize) {
            printf("Invalid request position!\n");
            free(requests);
            return 0;
        }
    }

    printf("Enter direction (1 for Right, 0 for Left): ");
    scanf("%d", &direction);

    if (direction != 0 && direction != 1) {
        printf("Invalid direction!\n");
        free(requests);
        return 0;
    }

    const char *names[] = {
        "FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK"
    };

    if (choice == 7) {
        printf("\n\t\t\t COMPARISON OF ALL ALGORITHMS \n");

        printf("%-12s %-22s %-20s\n",
               "Algorithm", "Head Movement", "Execution Time");

        for (int alg = FCFS; alg <= CLOOK; alg++) {
            double timeTaken;

            int movement = runAlgorithm( alg, requests, n, head, diskSize, direction, 0, &timeTaken);

            printf("%-12s %-22d %.6f seconds\n", names[alg - 1], movement, timeTaken);
        }

        printf("\nIndividual Seek Sequences:\n");

        for (int alg = FCFS; alg <= CLOOK; alg++) {
            double timeTaken;

            printf("\n%s:\n", names[alg - 1]);

            runAlgorithm(alg, requests, n, head,diskSize, direction, 1, &timeTaken);
        }
    }
    else {
        double timeTaken;

        printf("\n%s Disk Scheduling:\n", names[choice - 1]);

        runAlgorithm(choice, requests, n, head, diskSize, direction, 1, &timeTaken);
    }

    free(requests);

    return 0;
}
