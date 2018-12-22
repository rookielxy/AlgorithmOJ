#include <iostream>
#include <functional>
#include <queue>

using namespace std;

void swap(int &a, int &b);
void adjust(priority_queue<int, vector<int>, greater<int>> &, priority_queue<int> &);

int main() {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int data;
    while(scanf("%d", &data) > 0) {
        if(maxHeap.empty()) {
            maxHeap.push(data);
        } else if(data > maxHeap.top()){
            minHeap.push(data);
        } else {
            maxHeap.push(data);
        }
        adjust(minHeap, maxHeap);

        if(maxHeap.size() >= minHeap.size()) {
            printf("%d ", maxHeap.top());
        } else {
            printf("%d ", minHeap.top());
        }
    }
    printf("\n");
    return 0;
}

void adjust(priority_queue<int, vector<int>, greater<int>> &maxHeap, priority_queue<int> &minHeap) {
    if(maxHeap.size() > minHeap.size() + 1) {
        int data = maxHeap.top();
        maxHeap.pop();
        minHeap.push(data);
    } else if(minHeap.size() > maxHeap.size() + 1) {
        int data = minHeap.top();
        minHeap.pop();
        maxHeap.push(data);
    }
}