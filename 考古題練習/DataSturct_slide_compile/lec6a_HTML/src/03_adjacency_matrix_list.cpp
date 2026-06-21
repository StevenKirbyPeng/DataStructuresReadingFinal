#include <iostream>
#include <vector>
using namespace std;

// 同一張圖同時建立 adjacency matrix 與 adjacency list
int main() {
    int n = 5;
    vector<pair<int,int>> edges = {{0,1}, {0,2}, {1,3}, {2,3}, {3,4}};

    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);

    for (auto e : edges) {
        int u = e.first, v = e.second;
        matrix[u][v] = matrix[v][u] = 1; // 無向圖矩陣對稱
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "Adjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << matrix[i][j] << " ";
        cout << "\n";
    }

    cout << "Adjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : adj[i]) cout << v << " ";
        cout << "\n";
    }
    return 0;
}
