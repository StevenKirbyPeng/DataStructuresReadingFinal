#include <bits/stdc++.h>
using namespace std;

// AOE Critical Path
// Activity-on-Edge：edge 是活動與 duration，vertex 是事件。
// forward pass 算 earliest event time，backward pass 算 latest event time。

struct Edge {
    int from;
    int to;
    int duration;
    string name;
};

int main() {
    const int n = 7; // events 0..6
    vector<Edge> edges = {
        {0, 1, 6, "a1"},
        {0, 2, 4, "a2"},
        {1, 3, 1, "a3"},
        {2, 3, 1, "a4"},
        {2, 4, 9, "a5"},
        {3, 5, 7, "a6"},
        {4, 5, 2, "a7"},
        {5, 6, 4, "a8"}
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
    vector<int> indegreeCopy = indegree;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int ei : adj[u]) {
            int v = edges[ei].to;
            if (--indegreeCopy[v] == 0) q.push(v);
        }
    }

    vector<int> earliest(n, 0);
    for (int u : topo) {
        for (int ei : adj[u]) {
            const Edge& e = edges[ei];
            earliest[e.to] = max(earliest[e.to], earliest[e.from] + e.duration);
        }
    }

    int projectDuration = earliest[topo.back()];
    vector<int> latest(n, projectDuration);

    for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
        int u = *it;
        for (int ei : adj[u]) {
            const Edge& e = edges[ei];
            latest[e.from] = min(latest[e.from], latest[e.to] - e.duration);
        }
    }

    cout << "Project duration = " << projectDuration << "\n\n";
    cout << "Critical activities have slack = 0:\n";

    for (const Edge& e : edges) {
        int slack = latest[e.to] - earliest[e.from] - e.duration;
        cout << e.name << " (" << e.from << " -> " << e.to
             << ", duration=" << e.duration << ") slack = " << slack;
        if (slack == 0) cout << "  CRITICAL";
        cout << '\n';
    }

    return 0;
}