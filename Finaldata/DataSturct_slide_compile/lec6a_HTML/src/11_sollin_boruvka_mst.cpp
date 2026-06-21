#include <iostream>
#include <vector>
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
        return parent[x] == x ? x : parent[x] = find(parent[x]);
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
    DSU dsu(n);
    int components = n;
    int totalCost = 0;

    cout << "Boruvka MST steps:\n";
    while (components > 1) {
        vector<int> cheapest(n, -1);

        // 每個 component 找一條連出去的最便宜邊
        for (int i = 0; i < (int)edges.size(); i++) {
            int a = dsu.find(edges[i].u);
            int b = dsu.find(edges[i].v);
            if (a == b) continue;
            if (cheapest[a] == -1 || edges[i].w < edges[cheapest[a]].w) cheapest[a] = i;
            if (cheapest[b] == -1 || edges[i].w < edges[cheapest[b]].w) cheapest[b] = i;
        }

        for (int i = 0; i < n; i++) {
            int idx = cheapest[i];
            if (idx != -1 && dsu.unite(edges[idx].u, edges[idx].v)) {
                totalCost += edges[idx].w;
                components--;
                cout << "add edge " << edges[idx].u << "-" << edges[idx].v
                     << " weight " << edges[idx].w << "\n";
            }
        }
    }

    cout << "MST total cost = " << totalCost << "\n";
    return 0;
}
