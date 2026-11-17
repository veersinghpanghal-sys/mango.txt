
#include <bits/stdc++.h>
using namespace std;

int lru(vector<int>& pages, int n, int capacity) {
    unordered_set<int> memory;
    unordered_map<int, int> lastUsed;
    vector<int> frames(capacity, -1);

    int pageFaults = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        time++;

        bool hit = memory.count(page);

        if (hit) {
            // Update the last access time
            lastUsed[page] = time;
        }
        else {
            pageFaults++;

            if (memory.size() == capacity) {
                // Find the least recently used page
                int lruPage = -1;
                int oldestTime = INT_MAX;

                for (int p : memory) {
                    if (lastUsed[p] < oldestTime) {
                        oldestTime = lastUsed[p];
                        lruPage = p;
                    }
                }

                // Remove the LRU page
                memory.erase(lruPage);
                lastUsed.erase(lruPage);

                // Replace it in the frame vector
                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == lruPage) {
                        frames[j] = page;
                        break;
                    }
                }
            }
            else {
                // Put the page in an empty frame
                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == -1) {
                        frames[j] = page;
                        break;
                    }
                }
            }

            memory.insert(page);
            lastUsed[page] = time;
        }

        // Print current memory frames
        cout << page << " -> [ ";

        for (int p : frames) {
            if (p == -1)
                cout << "- ";
            else
                cout << p << " ";
        }

        cout << "] " << (hit ? "Hit" : "Fault") << '\n';
    }

    cout << "Total Page Faults: " << pageFaults << '\n';

    return pageFaults;
}

int main() {
    vector<int> pages = {1, 3, 0, 1, 5, 6};
    int capacity = 3;

    int pageFaults = lru(pages, pages.size(), capacity);

    return 0;
}
