#include <iostream>
using namespace std;

// linked representation：每個節點有 data、left、right 三個欄位
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) : data(x), left(nullptr), right(nullptr) {}
};

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

int main() {
    Node* root = new Node('A');
    root->left = new Node('B');
    root->right = new Node('C');
    root->left->left = new Node('D');
    root->left->right = new Node('E');

    cout << "Inorder traversal of linked binary tree: ";
    inorder(root);
    cout << '\n';
    return 0;
}