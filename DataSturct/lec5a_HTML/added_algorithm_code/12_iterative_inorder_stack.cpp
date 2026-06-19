#include <iostream>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) : data(x), left(nullptr), right(nullptr) {}
};

void iterativeInorder(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    while (cur != nullptr || !st.empty()) {
        while (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();
        cout << cur->data << ' ';
        cur = cur->right;
    }
}

int main() {
    Node* A = new Node('A');
    A->left = new Node('B');
    A->right = new Node('C');
    A->left->left = new Node('D');
    A->left->right = new Node('E');

    cout << "Iterative inorder: ";
    iterativeInorder(A);
    cout << '\n';
    return 0;
}