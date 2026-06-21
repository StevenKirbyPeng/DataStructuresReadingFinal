#include <bits/stdc++.h>
using namespace std;

// Bellman-Ford Algorithm
// 可處理 negative edge weight，但不能有 reachable negative cycle。
// 核心：重複 V-1 輪 relax 所有 edges，最後再檢查負 cycle。

struct Edge {
    int from;
    int to;
    int weight;
};

int main() {
    const int INF = 1e9;
    const int n = 6;

    vector<Edge> edges = {
        {0, 1, 6},
        {0, 2, 5},
        {1, 3, -2},
        {2, 1, 1},
        {2, 4, -1},
        {3, 5, 3},
        {4, 5, 7}
    };

    int source = 0;
    vector<int> dist(n, INF), parent(n, -1);
    dist[source] = 0;

    for (int round = 1; round <= n - 1; ++round) {
        bool changed = false;
        cout << "Round " << round << ":\n";

        for (const Edge& e : edges) {
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
                parent[e.to] = e.from;
                changed = true;
                cout << "  Relax " << e.from << " -> " << e.to
                     << ", dist[" << e.to << "] = " << dist[e.to] << '\n';
            }
        }

        if (!changed) {
            cout << "  No update, stop early.\n";
            break;
        }
    }

    bool hasNegativeCycle = false;
    for (const Edge& e : edges) {
        if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
            hasNegativeCycle = true;
        }
    }

    if (hasNegativeCycle) {
        cout << "\nNegative cycle detected. Shortest path is undefined.\n";
    } else {
        cout << "\nFinal distances:\n";
        for (int i = 0; i < n; ++i) {
            cout << "vertex " << i << ": dist = ";
            if (dist[i] == INF) cout << "INF";
            else cout << dist[i];
            cout << ", parent = " << parent[i] << '\n';
        }
    }

    return 0;
}