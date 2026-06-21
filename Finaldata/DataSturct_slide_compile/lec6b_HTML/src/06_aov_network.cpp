#include <bits/stdc++.h>
using namespace std;

// AOV Network
// Activity-on-Vertex：vertex 是活動，edge 是先修關係。
// 本程式建立課程先修圖，檢查每個活動的 predecessor / successor 與 indegree。

int main() {
    vector<string> course = {"C1", "C2", "C3", "C6", "C7", "C8", "C9", "C10", "C11"};
    int n = course.size();

    map<string, int> id;
    for (int i = 0; i < n; ++i) id[course[i]] = i;

    vector<pair<string,string>> prerequisites = {
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

    for (auto [pre, next] : prerequisites) {
        int u = id[pre], v = id[next];
        graph[u].push_back(v);
        indegree[v]++;
    }

    cout << "AOV Network: vertex = activity, edge = prerequisite relation\n\n";

    for (int i = 0; i < n; ++i) {
        cout << course[i] << ": indegree = " << indegree[i] << ", successors = ";
        for (int v : graph[i]) cout << course[v] << ' ';
        cout << '\n';
    }

    cout << "\nActivities with zero indegree can be scheduled first:\n";
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) cout << course[i] << ' ';
    }
    cout << '\n';

    return 0;
}