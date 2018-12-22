#include <iostream>

#define MAX_LENGTH 100000

using namespace std;

int main() {
    int* arr = new int[MAX_LENGTH];
    int number = 0, data;
    while(cin >> data) {
        arr[number] = data;
        ++number;
    }
    int sum = 0, max = 0;
    for(int i = 0; i < number; ++i) {
        sum += arr[i];
        if(sum > max) {
            max = sum;
        } else if(sum < 0) {
            sum = 0;
        }
    }
    cout << max << endl;
    return 0;
}