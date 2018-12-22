#include <iostream>
#include <algorithm>

using namespace std;

int findDouble(const int *list, int num, int target);
int findTripple(int *list, int num, int target);

int main() {
    int num, target;
    cin >> num >> target;
    int *list = new int[num];
    for(int i = 0; i < num; ++i) {
        cin >> list[i];
    }
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    cout << findTripple(list, num, target) << endl;
    return 0;
}

int findDouble(const int *list, int num, int target) {
    // already sorted
    int result = 0;
    int p = 0, q = num - 1;
    while(p < num && q > 0 && p != q) {
        if(list[p] + list[q] == target) {
            ++result;
            ++p;
        } else if(list[p] + list[q] < target){
            ++p;
        } else {
            --q;
        }
    }
    return result;
}

int findTripple(int *list, int num, int target) {
    sort(list, list + num);
    int result = 0;
    for(int i = 0; i < num; ++i) {
        result += findDouble(list + i + 1, num - i - 1, target - list[i]);
    }
    return result;
}