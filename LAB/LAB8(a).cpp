
#include <bits/stdc++.h>
using namespace std;

int fifo(vector<int>& pages, int n, int capacity)
{
    unordered_set<int> s;
    queue<int> indexes;
    vector<int> frames(capacity, -1);

    int page_faults = 0;
    int next = 0;

    for (int i = 0; i < n; i++)
    {
        int current_page = pages[i];
        bool found = (s.find(current_page) != s.end());

        if (!found)
        {
            page_faults++;

            if (s.size() < capacity)
            {
                frames[next] = current_page;
                next = (next + 1) % capacity;
            }
            else
            {
                int value = indexes.front();
                indexes.pop();
                s.erase(value);

                frames[next] = current_page;
                next = (next + 1) % capacity;
            }

            s.insert(current_page);
            indexes.push(current_page);
        }

        cout << current_page << " -> [ ";

        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] == -1)
                cout << "- ";
            else
                cout << frames[j] << " ";
        }

        cout << "] " << (found ? "Hit" : "Fault") << '\n';
    }

    cout << "Total Page Faults: " << page_faults << '\n';
    return page_faults;
}

int main()
{
    vector<int> pages = {1, 3, 0, 1, 5, 6, 0};
    int n = pages.size();
    int capacity = 3;

    int page_faults = fifo(pages, n, capacity);

    return 0;
}
