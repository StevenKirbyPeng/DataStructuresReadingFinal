#include <iostream>
#include <vector>
using namespace std;

// 節點結構：data 是節點名稱，children 儲存所有子節點
struct Node {
    char data;
    vector<Node*> children;
    Node(char x) : data(x) {}
};

// 計算樹高：空樹高度為 0，只有根節點高度為 1
int height(Node* root) {
    if (root == nullptr) return 0;
    int maxChildHeight = 0;
    for (Node* child : root->children) {
        maxChildHeight = max(maxChildHeight, height(child));
    }
    return maxChildHeight + 1;
}

// 計算節點數
int countNodes(Node* root) {
    if (root == nullptr) return 0;
    int total = 1;
    for (Node* child : root->children) total += countNodes(child);
    return total;
}

// 計算葉節點數：沒有 child 的節點就是 leaf
int countLeaves(Node* root) {
    if (root == nullptr) return 0;
    if (root->children.empty()) return 1;
    int total = 0;
    for (Node* child : root->children) total += countLeaves(child);
    return total;
}

int main() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    A->children = {B, C, D};
    B->children = {E};

    cout << "Root = " << A->data << '\n';
    cout << "Degree(A) = " << A->children.size() << '\n';
    cout << "Total nodes = " << countNodes(A) << '\n';
    cout << "Leaves = " << countLeaves(A) << '\n';
    cout << "Height = " << height(A) << '\n';
    return 0;
}