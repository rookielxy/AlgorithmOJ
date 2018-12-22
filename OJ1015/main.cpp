#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int lps(const string &str);

int main() {
    string str;
    char ch;
    while(scanf("%c ", &ch) > 0) {
        str += ch;
    }
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << lps(str) << endl;
    return 0;
}

int lps(const string &str) {
    short **table = new short*[str.size()];
    for(int i = 0; i < str.size(); ++i) {
        table[i] = new short[str.size()];
        memset(table[i], 0, str.size());
        table[i][i] = 1;
    }
    for(int i = 0; i < str.size(); ++i) {
        for(int j = i - 1; j >= 0; --j) {
            if(str[i] == str[j]) {
                table[j][i] = table[j + 1][i - 1] + (short)2;
            } else {
                table[j][i] = (table[j + 1][i] > table[j][i - 1])?
                              table[j + 1][i]: table[j][i - 1];
            }
        }
    }
    return table[0][str.size() - 1];
}