#include <iostream>
using namespace std;

// Left-Child Right-Sibling 節點：left 指向第一個孩子，right 指向下一個兄弟
struct Node {
    char data;
    Node* leftChild;
    Node* rightSibling;
    Node(char x) : data(x), leftChild(nullptr), rightSibling(nullptr) {}
};

void printLCRS(Node* root, int level = 0) {
    if (!root) return;
    for (int i = 0; i < level; ++i) cout << "  ";
    cout << root->data << '\n';
    printLCRS(root->leftChild, level + 1);   // 往下一層 child
    printLCRS(root->rightSibling, level);    // 同一層 sibling
}

int main() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    A->leftChild = B;
    B->rightSibling = C;
    C->rightSibling = D;
    B->leftChild = E;

    cout << "LCRS representation:\n";
    printLCRS(A);
    return 0;
}