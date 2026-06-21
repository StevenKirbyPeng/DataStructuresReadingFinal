#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    bool rightThread;
    Node(char x) : data(x), left(nullptr), right(nullptr), rightThread(false) {}
};

// 在 parent 的右邊插入 child，並維持簡化版 threaded link
void insertRight(Node* parent, Node* child) {
    child->right = parent->right;
    child->rightThread = parent->rightThread;
    parent->right = child;
    parent->rightThread = false;
}

void printRightChain(Node* root) {
    Node* cur = root;
    while (cur) {
        cout << cur->data << ' ';
        cur = cur->right;
    }
}

int main() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    A->right = nullptr;
    A->rightThread = true;

    insertRight(A, B);
    cout << "After InsertRight(A, B): ";
    printRightChain(A);
    cout << '\n';
    return 0;
}