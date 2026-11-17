#include<stdio.h>
#define MAX_FRAMES 3

void fifo (int pages[], int num_pages) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;
    int page_faults = 0, next_frame = 0;
    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        int found = 0;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == current_page) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[next_frame] = current_page;
            next_frame = (next_frame + 1) % MAX_FRAMES;
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
    fifo(pages, n);
return 0;
}