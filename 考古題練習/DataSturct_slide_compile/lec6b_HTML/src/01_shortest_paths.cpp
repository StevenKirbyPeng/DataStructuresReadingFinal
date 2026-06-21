#include <bits/stdc++.h>
using namespace std;

// Shortest Paths 總覽：列舉 source 到 destination 的簡單路徑，並計算總權重。
// 重點：path length = path 上所有 edge weight 的總和。

struct Edge {
    int to;
    int weight;
};

void dfsAllPaths(int u, int target,
                 const vector<vector<Edge>>& graph,
                 vector<int>& path,
                 vector<bool>& visited,
                 int cost,
                 int& bestCost,
                 vector<int>& bestPath) {
    if (u == target) {
        cout << "Path: ";
        for (int x : path) cout << x << ' ';
        cout << " cost = " << cost << '\n';

        if (cost < bestCost) {
            bestCost = cost;
            bestPath = path;
        }
        return;
    }

    visited[u] = true;
    for (const Edge& e : graph[u]) {
        if (!visited[e.to]) {
            path.push_back(e.to);
            dfsAllPaths(e.to, target, graph, path, visited,
                        cost + e.weight, bestCost, bestPath);
            path.pop_back();
        }
    }
    visited[u] = false;
}

int main() {
    const int n = 6;
    vector<vector<Edge>> graph(n);

    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
    };

    addEdge(0, 1, 50);
    addEdge(0, 2, 45);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(1, 3, 15);
    addEdge(3, 4, 15);
    addEdge(4, 1, 20);
    addEdge(4, 2, 35);
    addEdge(4, 5, 3);
    addEdge(2, 5, 30);

    int source = 0, target = 5;
    vector<int> path = {source};
    vector<bool> visited(n, false);
    int bestCost = INT_MAX;
    vector<int> bestPath;

    dfsAllPaths(source, target, graph, path, visited, 0, bestCost, bestPath);

    cout << "\nShortest path from " << source << " to " << target << ": ";
    for (int x : bestPath) cout << x << ' ';
    cout << "\nShortest distance = " << bestCost << '\n';

    return 0;
}