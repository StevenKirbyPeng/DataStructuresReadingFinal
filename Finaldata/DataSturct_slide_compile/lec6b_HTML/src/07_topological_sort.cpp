#include <bits/stdc++.h>
using namespace std;

// Topological Sort using Kahn's Algorithm
// 適用於 DAG。若排序後輸出的 vertex 數量少於 V，代表圖中有 cycle。

int main() {
    vector<string> course = {"C1", "C2", "C3", "C6", "C7", "C8", "C9", "C10", "C11"};
    int n = course.size();

    map<string, int> id;
    for (int i = 0; i < n; ++i) id[course[i]] = i;

    vector<pair<string,string>> edges = {
        {"C1", "C3"},
        {"C1", "C6"},
        {"C2", "C6"},
        {"C3", "C7"},
        {"C6", "C8"},
        {"C7", "C10"},
        {"C8", "C10"},
        {"C9", "C11"}
    };

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);

    for (auto [a, b] : edges) {
        int u = id[a], v = id[b];
        graph[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        cout << "Output " << course[u] << ", remove outgoing edges\n";

        for (int v : graph[u]) {
            indegree[v]--;
            cout << "  indegree[" << course[v] << "] = " << indegree[v] << '\n';
            if (indegree[v] == 0) q.push(v);
        }
    }

    if ((int)order.size() != n) {
        cout << "\nCycle exists. Topological order is impossible.\n";
    } else {
        cout << "\nTopological order:\n";
        for (int u : order) cout << course[u] << ' ';
        cout << '\n';
    }

    return 0;
}