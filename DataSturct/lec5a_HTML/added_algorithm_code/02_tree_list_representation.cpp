#include <iostream>
#include <vector>
using namespace std;

// 使用 adjacency list 表示一般樹：tree[i] 儲存節點 i 的所有 children
void printTree(const vector<vector<int>>& tree, int root, int level = 0) {
    for (int i = 0; i < level; ++i) cout << "  ";
    cout << "Node " << root << '\n';
    for (int child : tree[root]) {
        printTree(tree, child, level + 1);
    }
}

int main() {
    vector<vector<int>> tree(7);
    tree[0] = {1, 2, 3};
    tree[1] = {4, 5};
    tree[3] = {6};

    cout << "General tree using list representation:\n";
    printTree(tree, 0);
    return 0;
}