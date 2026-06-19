#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    bool rightThread; // true 代表 right 指向 inorder successor
    Node(char x) : data(x), left(nullptr), right(nullptr), rightThread(false) {}
};

Node* leftMost(Node* cur) {
    while (cur && cur->left) cur = cur->left;
    return cur;
}

void threadedInorder(Node* root) {
    Node* cur = leftMost(root);
    while (cur) {
        cout << cur->data << ' ';
        if (cur->rightThread) cur = cur->right;
        else cur = leftMost(cur->right);
    }
}

int main() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    A->left = B;
    A->right = C;
    B->right = A;       // B 的 inorder successor 是 A
    B->rightThread = true;

    cout << "Threaded inorder: ";
    threadedInorder(A);
    cout << '\n';
    return 0;
}