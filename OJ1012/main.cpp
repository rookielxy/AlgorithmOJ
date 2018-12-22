#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

enum State {white, gray, black};

struct Vertex {
    int idx;
    int depth;
    State state;
    vector<int> edge;
    Vertex() {
        depth = -1;
        idx = -1;
        state = white;
    }
};

bool operator< (Vertex v1, Vertex v2);
void BFS(vector<Vertex> &vertexs, int v);

queue<int> vertQueue;

int main() {
    vector<Vertex> vertexs;
    string str;
    while(getline(cin, str)) {
        Vertex newVert;
        stringstream stream;
        stream << str;
        stream >> newVert.idx;
        int dest = 0;
        while(stream >> dest) {
            newVert.edge.push_back(dest);
        }
        vertexs.push_back(newVert);
    }
    sort(vertexs.begin(), vertexs.end());
    BFS(vertexs, 0);
    vector<int> result;
    for(int i = 0; i < vertexs.size(); ++i) {
        if(vertexs[i].depth%2 == 0) {
            result.push_back(vertexs[i].idx);
        }
    }
    sort(result.begin(), result.end());
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    for(int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
    return 0;
}

bool operator< (Vertex v1, Vertex v2) {
    return (v1.idx < v2.idx);
}

void BFS(vector<Vertex> &vertexs, int v) {
    vertexs[v].state = gray;
    vertexs[v].depth = 0;
    vertQueue.push(v);
    while(!vertQueue.empty()) {
        int w = vertQueue.front();
        vertQueue.pop();
        for(int i = 0; i < vertexs[w].edge.size(); ++i) {
            int x = vertexs[w].edge[i];
            if(vertexs[x].state == white) {
                vertexs[x].state = gray;
                vertexs[x].depth = vertexs[w].depth + 1;
                vertQueue.push(x);
            }
        }
        vertexs[w].state = black;
    }
}