#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

#define INFINITE 2147483647

enum State {finished, fringe, future};

struct Edge {
    int dest;
    int cost;
    Edge() {
        dest = 0;
        cost = 0;
    }
    Edge(int dest, int cost) {
        this->dest = dest;
        this->cost = cost;
    }
};

struct Vertex {
    State state;
    int maxEdge;
    int heapIdx;
    vector<Edge> edge;
    Vertex() {
        heapIdx = -1;
        maxEdge = INFINITE;
        state = future;
    };
};

class PriorityHeap {
    vector<int> heap;
    Vertex *vertex;
private:
    bool compare(int v1, int v2) {
        return vertex[v1].maxEdge < vertex[v2].maxEdge;
    }

    void siftDown(int w) {
        int idx = vertex[w].heapIdx;
        int i = idx, j = 2*idx + 1;
        while(j <= heap.size()) {
            if(j < heap.size() && !compare(heap[j], heap[j + 1])) {
                ++j;
            }
            if(compare(w, heap[j])) {
                break;
            } else {
                heap[i] = heap[j];
                vertex[heap[i]].heapIdx = i;
                i = j;
                j = 2*j + 1;
            }
        }
        heap[i] = w;
        vertex[w].heapIdx = i;
    }

    void siftUp(int w) {
        int idx = vertex[w].heapIdx;
        int j = idx, i = (j - 1)/2;
        int temp = heap[j];
        while(j > 0) {
            if(compare(heap[i], temp)) {
                break;
            } else {
                heap[j] = heap[i];
                vertex[heap[j]].heapIdx = j;
                j = i;
                i = (i - 1)/2;
            }
        }
        heap[j] = temp;
        vertex[w].heapIdx = j;
    }
public:
    explicit PriorityHeap(Vertex *vertex, int n) {
        heap.reserve(n*sizeof(char));
        this->vertex = vertex;
    }

    void push(int v) {
        vertex[v].heapIdx = (int)(heap.size());
        heap.push_back(v);
        siftUp(v);
    }

    int top() {
        return heap.front();
    }

    void pop() {
        vertex[heap.front()].heapIdx = -1;
        heap.front() = heap.back();
        vertex[heap.front()].heapIdx = 0;
        heap.pop_back();

        siftDown(heap.front());
    }

    bool empty() {
        return heap.empty();
    }

    void decreaseKey(int w, int key) {
        vertex[w].maxEdge = key;
        siftUp(w);

    }
};

void findPath(Vertex *vertex, int s, int t, int n);
void updateFringe(Vertex *vertex, int v, PriorityHeap &queVert);

int main() {
    int n, s, t;
    cin >> n >> s >> t;
    auto vertex = new Vertex[n]();
    int cost, src, dest;
    while(cin >> cost >> src >> dest) {
        Edge edge1(dest, cost);
        vertex[src].edge.push_back(edge1);
        Edge edge2(src, cost);
        vertex[dest].edge.push_back(edge2);
    }
    findPath(vertex, s, t, n);
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << vertex[t].maxEdge << endl;
    return 0;
}

void findPath(Vertex *vertex, int s, int t, int n) {
    vertex[s].maxEdge = 0;
    vertex[s].state = finished;

    PriorityHeap queVert(vertex, n);
    for(int i = 0; i < vertex[s].edge.size(); ++i) {
        int w = vertex[s].edge[i].dest;
        vertex[w].state = fringe;
        vertex[w].maxEdge = vertex[s].edge[i].cost;
        queVert.push(w);
    }
    while(!queVert.empty() && vertex[t].state != finished) {
        int x = queVert.top();
        queVert.pop();
        vertex[x].state = finished;
        updateFringe(vertex, x, queVert);
    }
}

void updateFringe(Vertex *vertex, int v, PriorityHeap &queVert) {
    for(int i = 0; i < vertex[v].edge.size(); ++i) {
        int w = vertex[v].edge[i].dest;
        int cost = vertex[v].edge[i].cost;
        if(vertex[w].state == finished) {
            continue;
        } else {
            int maxEdge = (vertex[v].maxEdge > cost)? vertex[v].maxEdge: cost;
            if(vertex[w].maxEdge > maxEdge) {
                if(vertex[w].state == future) {
                    vertex[w].maxEdge = maxEdge;
                    vertex[w].state = fringe;
                    queVert.push(w);
                } else {
                    queVert.decreaseKey(w, maxEdge);
                }
            }
        }
    }
}

