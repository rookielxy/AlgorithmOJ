#include <iostream>

#define LENGTH 11

using namespace std;

bool stringLess(const char* str1, const char* str2);
long int mergeSort(char **strs, char **newStrs, int size);
void swap(char* &, char* &);
long int mergePart(char **strs, char **newStrs, int upperSize, int lowerSize);

int main() {
    int num;
    cin >> num;
    auto strs = new char*[num];
    auto newStrs = new char*[num];
    for(int i = 0; i < num; ++i) {
        strs[i] = new char[LENGTH];
        cin >> strs[i];
    }
    memcpy(newStrs, strs, num*sizeof(char*));
    long int reverse = mergeSort(strs, newStrs, num);
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    cout << reverse << endl;
    return 0;
}

bool stringLess(const char* str1, const char* str2) {
    return strcmp(str1, str2) < 0;
}

void swap(char* &str1, char* &str2) {
    char* temp = str1;
    str1 = str2;
    str2 = temp;
}

long int mergePart(char **strs, char **newStrs, int upperSize, int lowerSize) {
    long int reverse = 0;
    int counter = 0, upperCounter = 0, lowerCounter = 0;
    char **upperStrs = strs, **lowerStrs = strs + upperSize;
    while(counter < upperSize + lowerSize) {
        if(upperCounter == upperSize) {
            memcpy(&newStrs[counter], &lowerStrs[lowerCounter],
                   (lowerSize - lowerCounter)*sizeof(char*));
            break;
        } else if(lowerCounter == lowerSize) {
            memcpy(&newStrs[counter], &upperStrs[upperCounter],
                   (upperSize - upperCounter)*sizeof(char*));
            break;
        } else if(stringLess(upperStrs[upperCounter], lowerStrs[lowerCounter])) {
            newStrs[counter] = upperStrs[upperCounter];
            ++upperCounter;
        } else {
            newStrs[counter] = lowerStrs[lowerCounter];
            ++lowerCounter;
            reverse += (upperSize - upperCounter);
        }
        ++counter;
    }
    memcpy(strs, newStrs, (upperSize + lowerSize)*sizeof(char*));
    return reverse;
}

long int mergeSort(char **strs, char **newStrs, int size) {
    if(size == 1) {
        return 0;
    } else if(size == 2) {
        if(stringLess(strs[1], strs[0])) {
            swap(strs[0], strs[1]);
            swap(newStrs[0], newStrs[1]);
            return 1;
        } else {
            return 0;
        }
    } else {
        long int reverse = 0;
        int upperSize = size/2;
        int lowerSize = size - upperSize;
        reverse += mergeSort(strs, newStrs, upperSize);
        reverse += mergeSort(&strs[upperSize], &newStrs[upperSize], lowerSize);
        reverse += mergePart(strs, newStrs, upperSize, lowerSize);
        return reverse;
    }
}