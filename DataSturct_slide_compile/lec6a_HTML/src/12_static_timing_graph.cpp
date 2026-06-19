#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int to, delay;
};

int main() {
    int n = 6; // 0=S, 5=E
    vector<vector<Edge>> dag(n);
    vector<int> indeg(n, 0);

    auto addEdge = [&](int u, int v, int d) {
        dag[u].push_back({v, d});
        indeg[v]++;
    };

    addEdge(0,1,2);
    addEdge(0,2,3);
    addEdge(1,3,4);
    addEdge(2,3,1);
    addEdge(2,4,5);
    addEdge(3,5,2);
    addEdge(4,5,1);

    queue<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (Edge e : dag[u]) {
            indeg[e.to]--;
            if (indeg[e.to] == 0) q.push(e.to);
        }
    }

    vector<int> arrival(n, -1000000);
    arrival[0] = 0;

    // arrival time：從 S 到每個節點的 longest delay
    for (int u : topo) {
        for (Edge e : dag[u]) {
            arrival[e.to] = max(arrival[e.to], arrival[u] + e.delay);
        }
    }

    cout << "Topological order: ";
    for (int x : topo) cout << x << " ";
    cout << "\nArrival time:\n";
    for (int i = 0; i < n; i++) {
        cout << "node " << i << " = " << arrival[i] << "\n";
    }
    cout << "Critical delay from S to E = " << arrival[5] << "\n";
    return 0;
}
