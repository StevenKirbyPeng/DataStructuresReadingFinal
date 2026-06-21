#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

bool isFull(Node* root) {
    if (!root) return true;
    if (!root->left && !root->right) return true;
    if (root->left && root->right) return isFull(root->left) && isFull(root->right);
    return false;
}

bool isComplete(Node* root) {
    if (!root) return true;
    queue<Node*> q;
    q.push(root);
    bool seenNull = false;
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (!cur) seenNull = true;
        else {
            if (seenNull) return false;
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    return true;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Is full? " << (isFull(root) ? "Yes" : "No") << '\n';
    cout << "Is complete? " << (isComplete(root) ? "Yes" : "No") << '\n';
    return 0;
}