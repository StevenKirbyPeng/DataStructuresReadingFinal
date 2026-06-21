#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char x) : data(x), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Node* buildExpressionTree(const string& postfix) {
    stack<Node*> st;
    for (char c : postfix) {
        Node* node = new Node(c);
        if (isOperator(c)) {
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
        }
        st.push(node);
    }
    return st.top();
}

void inorder(Node* root) {
    if (!root) return;
    if (isOperator(root->data)) cout << '(';
    inorder(root->left);
    cout << root->data;
    inorder(root->right);
    if (isOperator(root->data)) cout << ')';
}

int main() {
    string postfix = "ab+c*";
    Node* root = buildExpressionTree(postfix);
    cout << "Postfix = " << postfix << '\n';
    cout << "Infix expression = ";
    inorder(root);
    cout << '\n';
    return 0;
}