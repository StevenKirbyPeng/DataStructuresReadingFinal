#include <bits/stdc++.h>
using namespace std;

// Dijkstra Algorithm
// 適用條件：所有 edge weight 都必須是 nonnegative。
// 核心：ExtractMin + Relax。

struct Edge {
    int to;
    int weight;
};

int main() {
    const int INF = 1e9;
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

    int source = 0;
    vector<int> dist(n, INF), parent(n, -1);
    vector<bool> fixed(n, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (fixed[u]) continue;
        fixed[u] = true;

        cout << "ExtractMin vertex " << u << ", dist = " << d << '\n';

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;

            if (!fixed[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
                cout << "  Relax " << u << " -> " << v
                     << ", new dist = " << dist[v] << '\n';
            }
        }
    }

    cout << "\nFinal shortest distances from source 0:\n";
    for (int i = 0; i < n; ++i) {
        cout << "vertex " << i << ": dist = ";
        if (dist[i] == INF) cout << "INF";
        else cout << dist[i];
        cout << ", parent = " << parent[i] << '\n';
    }

    return 0;
}