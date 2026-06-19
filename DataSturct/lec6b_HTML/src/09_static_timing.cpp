#include <bits/stdc++.h>
using namespace std;

// Static Timing Analysis on a DAG
// arrival：訊號最早/最慢到達時間
// required：訊號最晚必須到達時間
// slack = required - arrival

struct Edge {
    int from;
    int to;
    int delay;
};

int main() {
    const int n = 6; // simplified timing graph
    vector<string> name = {"IN1", "IN2", "G1", "G2", "G3", "OUT"};

    vector<Edge> edges = {
        {0, 2, 2},
        {1, 2, 3},
        {2, 3, 4},
        {2, 4, 2},
        {3, 5, 5},
        {4, 5, 1}
    };

    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    for (int i = 0; i < (int)edges.size(); ++i) {
        adj[edges[i].from].push_back(i);
        indegree[edges[i].to]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) if (indegree[i] == 0) q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int ei : adj[u]) {
            int v = edges[ei].to;
            if (--indegree[v] == 0) q.push(v);
        }
    }

    vector<int> arrival(n, 0);
    for (int u : topo) {
        for (int ei : adj[u]) {
            const Edge& e = edges[ei];
            arrival[e.to] = max(arrival[e.to], arrival[e.from] + e.delay);
        }
    }

    int clockRequired = 12;
    vector<int> required(n, clockRequired);

    for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
        int u = *it;
        for (int ei : adj[u]) {
            const Edge& e = edges[ei];
            required[e.from] = min(required[e.from], required[e.to] - e.delay);
        }
    }

    cout << "Clock required time = " << clockRequired << "\n\n";
    cout << "Node timing table:\n";
    for (int i = 0; i < n; ++i) {
        int slack = required[i] - arrival[i];
        cout << setw(4) << name[i]
             << " arrival=" << setw(2) << arrival[i]
             << " required=" << setw(2) << required[i]
             << " slack=" << setw(2) << slack;
        if (slack == 0) cout << "  CRITICAL";
        if (slack < 0) cout << "  VIOLATION";
        cout << '\n';
    }

    cout << "\nCritical path delay = " << arrival[5] << '\n';
    return 0;
}