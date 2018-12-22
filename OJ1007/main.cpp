#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_LENGTH 20

struct Box {
    char *str1;
    char *str2;
};

void findAnagram(Box *list, int num);
bool leqStr(char *str1, char *str2);
bool eqStr(char *str1, char *str2);
bool leqDictionary(char *str1, char *str2);
bool leqChar(char c1, char c2);
bool leqBox(Box b1, Box b2);


int main() {
    int num;
    cin >> num;
    Box *list = new Box[num];
    for(int i = 0; i < num; ++i) {
        list[i].str1 = new char[MAX_LENGTH];
        list[i].str2 = new char[MAX_LENGTH];
        cin >> list[i].str1;
        memcpy(list[i].str2, list[i].str1, strlen(list[i].str1));
    }
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    findAnagram(list, num);
    return 0;
}

bool leqStr(char *str1, char *str2) {
    if(strlen(str1) < strlen(str2)) {
        return true;
    } else if(strlen(str1) > strlen(str2)) {
        return false;
    } else {
        return strcmp(str1, str2) < 0;
    }
}

bool leqDictionary(char *str1, char *str2) {
    return strcmp(str1, str2) < 0;
}

bool leqChar(char c1, char c2) {
    return ((int)c1 < (int)c2);
}

bool leqBox(Box b1, Box b2) {
    if(leqStr(b1.str1, b2.str1)) {
        return true;
    } else if(strcmp(b1.str1, b2.str1) == 0) {
        return strcmp(b1.str2, b2.str2) < 0;
    } else {
        return false;
    }
}

void findAnagram(Box *list, int num) {
    vector<char*> record;

    for(int i = 0; i < num; ++i) {
        sort(list[i].str1, list[i].str1 + strlen(list[i].str1), leqChar);
    }
    sort(list, list + num, leqBox);

    int p = 0, q = 0;
    while(q < num) {
        while(q < num && strcmp(list[p].str1, list[q].str1) == 0) {
            ++q;
        }
        if(q - p > 1) {
            record.push_back(list[p].str2);
        }
        p = q;
    }

    cout << record.size() << endl;
    sort(record.begin(), record.end(), leqDictionary);
    for(int i = 0; i < record.size(); ++i) {
        cout << record[i] << endl;
    }
}