#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) : data(x), left(nullptr), right(nullptr) {}
};

bool eval(Node* root) {
    if (!root) return false;
    if (root->data == 'T') return true;
    if (root->data == 'F') return false;

    bool L = eval(root->left);
    bool R = eval(root->right);
    if (root->data == '&') return L && R;
    if (root->data == '|') return L || R;
    return false;
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << ' ';
}

int main() {
    Node* root = new Node('|');
    root->left = new Node('&');
    root->right = new Node('F');
    root->left->left = new Node('T');
    root->left->right = new Node('T');

    cout << "Postorder evaluation order: ";
    postorder(root);
    cout << "\nSAT result = " << (eval(root) ? "True" : "False") << '\n';
    return 0;
}