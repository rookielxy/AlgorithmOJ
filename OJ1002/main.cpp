#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void findAllPair(vector<int>&, int);

int main() {
    int n, c;
    while(cin >> n) {
        vector<int> arr;
        for(int i = 0; i < n; ++i) {
            int temp;
            cin >> temp;
            arr.push_back(temp);
        }
        cin >> c;
        findAllPair(arr, c);
    }
    return 0;
}

/*
void findAllPair(vector<int> &arr, int c) {
    for(int i = 0; i < arr.size(); ++i) {
        for(int j = i + 1; j < arr.size(); ++j) {
            if(arr[i] + arr[j] == c) {
                cout << arr[i] << " " << arr[j] << endl;
            }
        }
    }
}
*/

void findAllPair(vector<int> &arr, int c) {
    vector<int>::const_iterator p1 = arr.begin();
    vector<int>::const_iterator p2 = --arr.end();
    while(p1 != p2 && p1 != arr.end() && p2 != arr.begin()) {
        while (*p1 + *p2 != c && p1 != p2) {
            if (*p1 + *p2 < c) {
                ++p1;
            }
            else {
                --p2;
            }
        }
        if(p1 == p2) {
            break;
        }
        cout << *p1 << " " << *p2 << endl;
        ++p1;
    }
}