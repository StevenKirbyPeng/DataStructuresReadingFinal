#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

int main() {
    int n = 5;
    vector<Edge> edges = {{0,1,10}, {0,2,6}, {0,3,5}, {1,3,15}, {2,3,4}, {3,4,2}};

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    int totalCost = 0;
    cout << "Kruskal MST edges:\n";

    for (Edge e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalCost += e.w;
            cout << e.u << " - " << e.v << " weight " << e.w << "\n";
        }
    }

    cout << "MST total cost = " << totalCost << "\n";
    return 0;
}
