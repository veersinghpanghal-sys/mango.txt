
#include <bits/stdc++.h>
using namespace std;

int fifo(vector<int>& pages, int capacity) {
    unordered_set<int> memory;
    queue<int> order;
    vector<int> frames(capacity, -1);
    int pageFaults = 0;

    cout << "\n\t\t FIFO Page Replacement \n";

    for (int page : pages) {
        bool hit = memory.count(page);

        if (!hit) {
            pageFaults++;

            if (memory.size() == capacity) {
                int oldest = order.front();
                order.pop();
                memory.erase(oldest);

                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == oldest) {
                        frames[j] = page;
                        break;
                    }
                }
            }
            else {
                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == -1) {
                        frames[j] = page;
                        break;
                    }
                }
            }

            memory.insert(page);
            order.push(page);
        }

        cout << page << " -> [ ";
        for (int p : frames) {
            if (p == -1) cout << "- ";
            else cout << p << " ";
        }
        cout << "] " << (hit ? "Hit" : "Fault") << '\n';
    }

    cout << "FIFO Page Faults: " << pageFaults << '\n';
    return pageFaults;
}

int lru(vector<int>& pages, int capacity) {
    unordered_set<int> memory;
    unordered_map<int, int> lastUsed;
    vector<int> frames(capacity, -1);
    int pageFaults = 0, time = 0;

    cout << "\n\t\t LRU Page Replacement \n";

    for (int page : pages) {
        time++;
        bool hit = memory.count(page);

        if (hit) {
            lastUsed[page] = time;
        }
        else {
            pageFaults++;

            if (memory.size() == capacity) {
                int lruPage = -1;
                int oldestTime = INT_MAX;

                for (int p : memory) {
                    if (lastUsed[p] < oldestTime) {
                        oldestTime = lastUsed[p];
                        lruPage = p;
                    }
                }

                memory.erase(lruPage);
                lastUsed.erase(lruPage);

                for (int j = 0; j < capacity; j++) {
                    if (frames[j] == lruPage) {
                        frames[j] = page;
                        break;
                    }
                }
            }
            else {
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

        cout << page << " -> [ ";
        for (int p : frames) {
            if (p == -1) cout << "- ";
            else cout << p << " ";
        }
        cout << "] " << (hit ? "Hit" : "Fault") << '\n';
    }

    cout << "LRU Page Faults: " << pageFaults << '\n';
    return pageFaults;
}

int main() {
    vector<int> pages = {1, 2, 3, 1, 4, 2, 5};
    int capacity = 3;
    cout << endl;
    cout << "Reference String: ";
    for (int p : pages) cout << p << " ";
    cout << "\nNumber of Frames: " << capacity << '\n';

    int fifoFaults = fifo(pages, capacity);
    int lruFaults = lru(pages, capacity);

    cout << "\n\t\t Final Comparison \n";
    cout << "FIFO Page Faults: " << fifoFaults << '\n';
    cout << "LRU Page Faults:  " << lruFaults << '\n';

    if (fifoFaults < lruFaults)
        cout << "FIFO performed better for this reference string.\n";
    else if (lruFaults < fifoFaults)
        cout << "LRU performed better for this reference string.\n";
    else
        cout << "Both algorithms produced the same number of faults.\n";

    return 0;
}
