#include <iostream>
#include <vector>
using namespace std;

// 使用 1-based array 表示 complete binary tree
int parent(int i) { return i / 2; }
int leftChild(int i) { return 2 * i; }
int rightChild(int i) { return 2 * i + 1; }

int main() {
    vector<int> tree = {0, 10, 20, 30, 40, 50, 60}; // tree[0] 不使用
    int i = 3;

    cout << "Array representation of binary tree:\n";
    for (int idx = 1; idx < (int)tree.size(); ++idx) {
        cout << "index " << idx << " value " << tree[idx] << '\n';
    }
    cout << "Node index = " << i << '\n';
    cout << "Parent index = " << parent(i) << '\n';
    cout << "Left child index = " << leftChild(i) << '\n';
    cout << "Right child index = " << rightChild(i) << '\n';
    return 0;
}