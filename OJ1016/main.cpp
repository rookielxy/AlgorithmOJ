#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int minCover(const vector<vector<int>> &map);

int main() {
    string str;
    vector<vector<int>> map;
    while(getline(cin, str)) {
        stringstream stream;
        stream << str;
        vector<int> vertex;
        int edge;
        stream >> edge;
        while(stream >> edge) {
            vertex.push_back(edge);
        }
        map.push_back(vertex);
    }
    vector<vector<int>> rmap(map.size());
    for(int i = 0; i < map.size(); ++i) {
        for(int j = 0; j < map[i].size(); ++j) {
            int child = map[i][j];
            rmap[child].push_back(i);
        }
    }
    auto covered = new bool[rmap.size()];
    auto selected = new bool[rmap.size()];
    memset(covered, false, rmap.size());
    memset(selected, false, rmap.size());
    for(int i = (int)rmap.size() - 1; i > 0; --i) {
        int parent = rmap[i][0];
        if(!covered[i] && !covered[parent]) {
            covered[i] = true;
            covered[parent] = true;
            selected[parent] = true;
        }
    }
    for(auto child: map[0]) {
        if(!covered[child]) {
            selected[0] = true;
            break;
        }
    }
    int result = 0;
    for(int i = 0; i < rmap.size(); ++i) {
        if(selected[i]) {
            ++result;
        }
    }
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << result << endl;
    return 0;
}