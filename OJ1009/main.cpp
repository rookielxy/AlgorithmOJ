#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

enum State {white, gray, black};

struct Edge {
    int src;
    int dest;
};

struct Vertex {
    State state;
    int discoverTime;
    int depth;
    int back;
    vector<int> edges;
    Vertex() {
        state = white;
        discoverTime = 0;
        depth = 0;
        back = 0;
    }
};

int n = 0;

void addEdge(Vertex *vertexs, int src, int dest);
void findAllCut(Vertex *vertexs, vector<int> &cutPoint, vector<Edge> &bridge);
void DFS(Vertex *vertexs, int v, vector<int> &cutPoint, vector<Edge> &bridge, int time);
bool operator== (Edge e1, Edge e2);
bool operator< (Edge e1, Edge e2);
bool operator> (Edge e1, Edge e2);

int main() {
    cin >> n;
    auto vertexs = new Vertex[n]();
    int src, dest;
    while(cin >> src >> dest) {
        addEdge(vertexs, src, dest);
        addEdge(vertexs, dest, src);
    }
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    vector<int> cutPoint;
    vector<Edge> bridge;
    findAllCut(vertexs, cutPoint, bridge);
    sort(cutPoint.begin(), cutPoint.end());
    sort(bridge.begin(), bridge.end());
    for(auto i: cutPoint) {
        cout << i << endl;
    }
    for(auto i: bridge) {
        cout << i.src << " " << i.dest << endl;
    }

    return 0;
}

void addEdge(Vertex *vertexs, int src, int dest) {
    vertexs[src].edges.push_back(dest);
}

void findAllCut(Vertex *vertexs, vector<int> &cutPoint, vector<Edge> &bridge) {
    for(int i = 0; i < n; ++i) {
        vertexs[i].state = white;
        vertexs[i].discoverTime = 0;
        vertexs[i].depth = 0;
    }
    int time = 0;
    for(int i = 0; i < n; ++i) {
        if(vertexs[i].state == white) {
            DFS(vertexs, i, cutPoint, bridge, time);
            int treeEdge = 0;
            for(int j = 0; j < vertexs[i].edges.size(); ++j) {
                int w = vertexs[i].edges[j];
                if(vertexs[w].depth == 1) {
                    ++treeEdge;
                }
            }
            if(treeEdge <= 1) {
                auto it = find(cutPoint.begin(), cutPoint.end(), i);
                cutPoint.erase(it);
            }
        }
    }
}

void DFS(Vertex *vertexs, int v, vector<int> &cutPoint, vector<Edge> &bridge, int time) {
    vertexs[v].state = gray;
    vertexs[v].discoverTime = time;
    vertexs[v].back = vertexs[v].discoverTime;
    ++time;

    for(int i = 0; i < vertexs[v].edges.size(); ++i) {
        int w = vertexs[v].edges[i];
        if(vertexs[w].state == white) {
            vertexs[w].depth = vertexs[v].depth + 1;
            DFS(vertexs, w, cutPoint, bridge, time);
            if(vertexs[w].back >= vertexs[v].discoverTime) {
                auto it = find(cutPoint.begin(), cutPoint.end(), v);
                if (it == cutPoint.end()) {
                    cutPoint.push_back(v);
                }
            }
            if(vertexs[w].back > vertexs[v].discoverTime) {
                auto edge = new Edge();
                edge->src = (v < w)? v: w;
                edge->dest = (v < w)? w: v;
                auto it = find(bridge.begin(), bridge.end(), *edge);
                if(it == bridge.end()) {
                    bridge.push_back(*edge);
                }
            }
            vertexs[v].back = (vertexs[v].back < vertexs[w].back)?
                              vertexs[v].back: vertexs[w].back;
        } else if(vertexs[w].state == gray) {
            if(vertexs[w].depth < vertexs[v].depth - 1) {
                vertexs[v].back = (vertexs[v].back < vertexs[w].discoverTime) ?
                                  vertexs[v].back : vertexs[w].discoverTime;
            }
        }
    }
    vertexs[v].state = black;
}

bool operator== (Edge e1, Edge e2) {
    return (e1.src == e2.src && e1.dest == e2.dest) ||
            (e1.src == e2.dest && e1.dest == e2.src);
}

bool operator< (Edge e1, Edge e2) {
    return (e1.src < e2.src) ||
            (e1.src == e2.src && e1.dest < e2.dest);
}

bool operator> (Edge e1, Edge e2) {
    return (e1.src > e2.src) ||
            (e1.src == e2.src && e1.dest > e2.dest);
}