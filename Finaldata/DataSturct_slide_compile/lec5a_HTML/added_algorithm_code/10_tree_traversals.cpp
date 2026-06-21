#include <iostream>
using namespace std;

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

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << ' ';
}

int main() {
    Node* A = new Node('A');
    A->left = new Node('B');
    A->right = new Node('C');
    A->left->left = new Node('D');
    A->left->right = new Node('E');

    cout << "Preorder: "; preorder(A); cout << '\n';
    cout << "Inorder: "; inorder(A); cout << '\n';
    cout << "Postorder: "; postorder(A); cout << '\n';
    return 0;
}