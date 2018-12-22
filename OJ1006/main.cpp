#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

#define nullptr NULL

struct Node {
    int val;
    Node *left;
    Node *right;
    explicit Node(int input) {
        val = input;
        left = nullptr;
        right = nullptr;
    }
};

int getHeight(Node *);
int getDiameter(Node *);
Node *buildTree(vector<int> pre, vector<int> mid);

int main() {
    int num;
    cin >> num;
    vector<int> pre, mid;
    for(int i = 0; i < num; ++i) {
        int data;
        cin >> data;
        pre.push_back(data);
    }
    for(int i = 0; i < num; ++i) {
        int data;
        cin >> data;
        mid.push_back(data);
    }
    Node *root = buildTree(pre, mid);
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << getHeight(root) << endl;
    cout << getDiameter(root) << endl;
    return 0;
}

Node *buildTree(vector<int> pre, vector<int> mid) {
    assert(pre.size() == mid.size());
    if(pre.empty()) {
        return nullptr;
    }

    Node *p = new Node(pre.front());
    int flag = pre.front();
    vector<int> lmid, rmid;
    bool find = false;
    for(int i = 0; i < mid.size(); ++i) {
        if(mid[i] == flag) {
            find = true;
            continue;
        }
        if(!find) {
            lmid.push_back(mid[i]);
        } else {
            rmid.push_back(mid[i]);
        }
    }

    vector<int> lpre, rpre;
    int i = 1;
    while(lpre.size() < lmid.size()) {
        lpre.push_back(pre[i]);
        ++i;
    }
    while(rpre.size() < rmid.size()) {
        rpre.push_back(pre[i]);
        ++i;
    }

    p->left = buildTree(lpre, lmid);
    p->right = buildTree(rpre, rmid);

    return p;
}

int getHeight(Node *root) {
    if(root == nullptr) {
        return -1;
    }
    int lheight = getHeight(root->left);
    int rheight = getHeight(root->right);
    return (lheight > rheight)? lheight + 1: rheight + 1;
}

int getDiameter(Node *root) {
    if(root == nullptr) {
        return 0;
    }
    int cross = getHeight(root->left) + getHeight(root->right) + 2;
    int inner = (getDiameter(root->left) > getDiameter(root->right))?
                getDiameter(root->left): getDiameter(root->right);
    return (cross > inner)? cross: inner;
}