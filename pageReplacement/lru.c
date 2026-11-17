
#include<stdio.h>
#define MAX_FRAMES 3

void lru(int pages[], int num_pages) {
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    int page_faults = 0;

    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == current_page) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;

            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    lruIndex = j;
                    break;
                }

                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            frames[lruIndex] = current_page;
            lastUsed[lruIndex] = i;
            page_faults++;
        }

        printf("%d -> [", current_page);

        for (int j = 0; j < MAX_FRAMES; j++) {
            frames[j] != -1 ? printf(" %d ", frames[j]) : printf(" - ");
        }

        printf("]\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main()
{
    int pages[] = {1, 3, 0, 1, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);

    lru(pages, n);

    return 0;
}
 