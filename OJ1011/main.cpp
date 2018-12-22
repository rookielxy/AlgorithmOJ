#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <stack>

using namespace std;

enum State {white, gray, black};

struct Vertex {
    State state;
    int block;
    vector<int> outEdge;
    vector<int> inEdge;
    Vertex() {
        state = white;
        block = 0;
    }
};

struct Block {
    State state;
    int impact;
    vector<int> vertex;
    vector<int> edge;
    Block() {
        state = white;
        impact = 0;
    }
};

void firstTraversal(vector<Vertex> &vertexs);
void outDFS(vector<Vertex> &vertexs, int v);
void fillInEdge(vector<Vertex> &vertexs);
vector<Block> secondTraversal(vector<Vertex> &vertexs);
void inDFS(vector<Vertex> &vertexs, Block &block, int v, int blockIdx);
void addBlockEdge(vector<Vertex> &vertexs, vector<Block> &blocks);
void blockTraversal(vector<Block> &blocks);
void blockDFS(vector<Block> &blocks, int v);

stack<int> vertStack;

int main() {
    vector<Vertex> vertexs;
    string str;
    while(getline(cin, str)) {
        Vertex newVert;
        stringstream stream;
        stream << str;
        int dest = 0;
        while(stream >> dest) 
            newVert.outEdge.push_back(dest);
        vertexs.push_back(newVert);
    }

    fillInEdge(vertexs);
    firstTraversal(vertexs);
    vector<Block> blocks = secondTraversal(vertexs);
    blockTraversal(blocks);
    int maxImpact = 0;
    for(int i = 0; i < blocks.size(); ++i) {
        maxImpact = (blocks[i].impact > maxImpact)? blocks[i].impact: maxImpact;
    }
    vector<int> result;
    for(int i = 0; i < blocks.size(); ++i) {
        if(blocks[i].impact == maxImpact) {
            for(int j = 0; j < blocks[i].vertex.size(); ++j) {
                result.push_back(blocks[i].vertex[j]);
            }
        }
    }
    sort(result.begin(), result.end());
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << maxImpact - 1 << endl;
    for(int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    return 0;
}

void firstTraversal(vector<Vertex> &vertexs) {
    for(int i = 0; i < vertexs.size(); ++i) {
        vertexs[i].state = white;
    }
    for(int i = 0; i < vertexs.size(); ++i) {
        if(vertexs[i].state == white) {
            outDFS(vertexs, i);
        }
    }
}

void outDFS(vector<Vertex> &vertexs, int v) {
    vertexs[v].state = gray;

    for(int i = 0; i < vertexs[v].outEdge.size(); ++i) {
        int w = vertexs[v].outEdge[i];
        if(vertexs[w].state == white) {
            outDFS(vertexs, w);
        }
    }
    vertStack.push(v);
    vertexs[v].state = black;
}

void fillInEdge(vector<Vertex> &vertexs) {
    for(int i = 0; i < vertexs.size(); ++i) {
        for(int j = 0;j < vertexs[i].outEdge.size(); ++j) {
            int dest = vertexs[i].outEdge[j];
            vertexs[dest].inEdge.push_back(i);
        }
    }
}

vector<Block> secondTraversal(vector<Vertex> &vertexs) {
    for(int i = 0; i < vertexs.size(); ++i) {
        vertexs[i].state = white;
    }
    vector<Block> blocks;
    int blockIdx = 0;
    while(!vertStack.empty()) {
        int v = vertStack.top();
        if(vertexs[v].state == white) {
            Block newBlock;
            inDFS(vertexs, newBlock, v, blockIdx);
            blocks.push_back(newBlock);
            ++blockIdx;
        }
        vertStack.pop();
    }
    addBlockEdge(vertexs, blocks);
    return blocks;
}

void inDFS(vector<Vertex> &vertexs, Block &block, int v, int blockIdx) {
    vertexs[v].state = gray;
    vertexs[v].block = blockIdx;
    block.vertex.push_back(v);
    for(int i = 0; i < vertexs[v].inEdge.size(); ++i) {
        int w = vertexs[v].inEdge[i];
        if(vertexs[w].state == white) {
            inDFS(vertexs, block, w, blockIdx);
        }
    }
    vertexs[v].state = black;
}

void addBlockEdge(vector<Vertex> &vertexs, vector<Block> &blocks) {
    for(int i = 0; i < vertexs.size(); ++i) {
        int srcBlock = vertexs[i].block;
        for(int j = 0; j < vertexs[i].outEdge.size(); ++j) {
            int w = vertexs[i].outEdge[j];
            int destBlock = vertexs[w].block;
            if(srcBlock != destBlock) {
                vector<int>::iterator it = find(blocks[srcBlock].edge.begin(),
                                                blocks[srcBlock].edge.end(),
                                                destBlock);
                if(it == blocks[srcBlock].edge.end())
                    blocks[srcBlock].edge.push_back(destBlock);
            }
        }
    }
}

void blockTraversal(vector<Block> &blocks) {
    bool *inEdge = new bool[blocks.size()];
    memset(inEdge, false, blocks.size()*sizeof(bool));
    for(int i = 0; i < blocks.size(); ++i) {
        for(int j = 0; j < blocks[i].edge.size(); ++j)
            inEdge[blocks[i].edge[j]] = true;
    }
    for(int i = 0; i < blocks.size(); ++i) {
        if(!inEdge[i]) {
            for(int j = 0; j < blocks.size(); ++j) {
                if(inEdge[j]) {
                    blocks[j].state = white;
                    blocks[j].impact = 0;
                }
            }
            blockDFS(blocks, i);
        }
    }
}

void blockDFS(vector<Block> &blocks, int v) {
    blocks[v].state = gray;
    blocks[v].impact += blocks[v].vertex.size();
    for(int i = 0; i < blocks[v].edge.size(); ++i) {
        int w = blocks[v].edge[i];
        if(blocks[w].state == white) {
            blockDFS(blocks, w);
            blocks[v].impact += blocks[w].impact;
        }

    }
    blocks[v].state = black;
}