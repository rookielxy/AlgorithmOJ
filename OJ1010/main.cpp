#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

enum State {white, gray, black};

struct Vertex {
    State state;
    int cost;
    int eft;
    int est;
    vector<int> edge;
    Vertex() {
        state = white;
        cost = 0;
        eft = 0;
        est = 0;
    };
};

int schedule(Vertex *vertexs, int n);
void DFS(Vertex *vertexs, int n, int v);

int main() {
    int n;
    cin >> n;
    Vertex *vertexs = new Vertex[n]();
    for(int i = 0; i < n; ++i) {
        int index;
        cin >> index >> vertexs[i].cost;
    }
    int src, dest;
    while(cin >> src >> dest) {
        vertexs[src - 1].edge.push_back(dest - 1);
    }

    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << schedule(vertexs, n) << endl;
    return 0;
}

int schedule(Vertex *vertexs, int n) {
    int max = 0;
    for(int i = 0; i < n; ++i) {
        if(vertexs[i].state == white) {
            DFS(vertexs, n, i);
            max = (vertexs[i].eft > max)? vertexs[i].eft: max;
        }
    }
    return max;
}

void DFS(Vertex *vertexs, int n, int v) {
    vertexs[v].state = gray;
    vertexs[v].est = 0;
    for(int i = 0; i < vertexs[v].edge.size(); ++i) {
        int w = vertexs[v].edge[i];
        if(vertexs[w].state == white) {
            DFS(vertexs, n, w);
        }
        vertexs[v].est = (vertexs[w].eft > vertexs[v].est)?
                         vertexs[w].eft: vertexs[v].est;
    }
    vertexs[v].eft = vertexs[v].est + vertexs[v].cost;
    vertexs[v].state = black;
}