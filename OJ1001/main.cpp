#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int k, n;
    while(cin >> k >> n) {
        int *data = new int[n];
        for(int i = 0; i < n; ++i) {
            cin >> data[i];
        }
        int *tail = data;
        tail += n;
        sort(data, tail);
        int start = 0;
        int  end = 0;
        if((n % 2) == 0) {
            start = n/2 - 1 - k;
            end = n/2 - 1 + k;
        }
        else {
            start = n/2 - k;
            end = n/2 + k;
        }
        for(int i = start; i <= end; ++i) {
            cout << data[i];
            if(i != end) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}