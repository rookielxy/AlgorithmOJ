#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <cstring>
#include <cassert>

using namespace std;

enum State {black, gray, white};

struct Edge {
    int dest;
    int cost;
    Edge() {
        dest = 0;
        cost = 0;
    }
};

struct Vertex {
    State state;
    int dist;
    vector<Edge> edge;
    Vertex() {
        state = white;
        dist = 0;
    }

};

void TopoSort(Vertex *vertex, int n);
void DFS(Vertex *vertex, int v);
void updateDist(Vertex *vertex, int v);

stack<int> topo;

int main() {
    int n;
    cin >> n;
    auto vertex = new Vertex[n]();
    int src, dest, cost;
    while(cin >> src >> dest >> cost) {
        Edge edge;
        edge.dest = dest;
        edge.cost = cost;
        vertex[src].edge.push_back(edge);
    }
    TopoSort(vertex, n);
    while(!topo.empty()) {
        int v = topo.top();
        updateDist(vertex, v);
        topo.pop();
    }
    cout << "I have read the rules about plagiarism punishment" << endl;
    for(int i = 1; i < n; ++i) {
        cout << vertex[i].dist << " ";
    }
    return 0;
}

void TopoSort(Vertex *vertex, int n) {
    for(int i = 0; i < n; ++i) {
        if(vertex[i].state == white) {
            DFS(vertex, i);
        }
    }
}

void DFS(Vertex *vertex, int v) {
    vertex[v].state = gray;
    for(int i = 0; i < vertex[v].edge.size(); ++i) {
        int w = vertex[v].edge[i].dest;
        assert(vertex[w].state != gray);
        if(vertex[w].state == white) {
            DFS(vertex, w);
        }
    }
    topo.push(v);
    vertex[v].state = black;
}

void updateDist(Vertex *vertex, int v) {
    for(int i = 0; i < vertex[v].edge.size(); ++i) {
        int w = vertex[v].edge[i].dest;
        int cost = vertex[v].edge[i].cost;
        vertex[w].dist = (vertex[w].dist > vertex[v].dist + cost)?
                         vertex[w].dist: vertex[v].dist + cost;
    }
}