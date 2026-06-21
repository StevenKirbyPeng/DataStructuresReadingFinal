#include <iostream>
#include <vector>
using namespace std;

void dfs(int u, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int v : graph[u]) {
        if (!visited[v]) dfs(v, graph, visited);
    }
}

int main() {
    vector<vector<int>> graph = {
        {1}, {0, 2}, {1}, // component 1: 0-1-2
        {4}, {3},        // component 2: 3-4
        {}               // component 3: 5
    };

    vector<bool> visited(graph.size(), false);
    int componentCount = 0;

    for (int i = 0; i < (int)graph.size(); i++) {
        if (!visited[i]) {
            componentCount++;
            cout << "component " << componentCount << ": ";
            dfs(i, graph, visited);
            cout << "\n";
        }
    }

    cout << "total components = " << componentCount << "\n";
    return 0;
}
