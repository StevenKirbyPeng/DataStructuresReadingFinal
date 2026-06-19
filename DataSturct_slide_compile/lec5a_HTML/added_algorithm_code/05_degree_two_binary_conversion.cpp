#include <iostream>
using namespace std;

// 一般樹轉二元樹：firstChild 當 left，nextSibling 當 right
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) : data(x), left(nullptr), right(nullptr) {}
};

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << ' ';
    preorder(root->left);
    preorder(root->right);
}

int main() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');

    // A 的 children 為 B, C, D；B 的 child 為 E
    A->left = B;
    B->right = C;
    C->right = D;
    B->left = E;

    cout << "Binary representation preorder: ";
    preorder(A);
    cout << '\n';
    return 0;
}