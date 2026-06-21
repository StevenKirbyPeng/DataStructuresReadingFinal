#include <iostream>
#include <vector>
using namespace std;

void dfs(int u, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";

    // DFS 會盡量往尚未拜訪的鄰居深入
    for (int v : graph[u]) {
        if (!visited[v]) {
            cout << "(tree edge " << u << "->" << v << ") ";
            dfs(v, graph, visited);
            cout << "(backtrack to " << u << ") ";
        }
    }
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1},
        {2}
    };
    vector<bool> visited(graph.size(), false);

    cout << "DFS order and traversal tree:\n";
    dfs(0, graph, visited);
    cout << "\n";
    return 0;
}
