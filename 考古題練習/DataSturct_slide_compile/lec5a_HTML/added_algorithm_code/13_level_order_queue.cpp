#include <iostream>
#include <queue>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) : data(x), left(nullptr), right(nullptr) {}
};

void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        cout << cur->data << ' ';
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

int main() {
    Node* A = new Node('A');
    A->left = new Node('B');
    A->right = new Node('C');
    A->left->left = new Node('D');
    A->left->right = new Node('E');

    cout << "Level-order traversal: ";
    levelOrder(A);
    cout << '\n';
    return 0;
}