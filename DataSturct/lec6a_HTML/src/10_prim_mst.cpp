#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int to, w;
};

int main() {
    int n = 5;
    vector<vector<Edge>> graph(n);
    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    };

    addEdge(0,1,10);
    addEdge(0,2,6);
    addEdge(0,3,5);
    addEdge(1,3,15);
    addEdge(2,3,4);
    addEdge(3,4,2);

    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({0, 0}); // {邊權重, 頂點}
    int totalCost = 0;

    cout << "Prim selected vertices:\n";
    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalCost += cost;
        cout << "add vertex " << u << " by cost " << cost << "\n";

        for (Edge e : graph[u]) {
            if (!inMST[e.to]) pq.push({e.w, e.to});
        }
    }

    cout << "MST total cost = " << totalCost << "\n";
    return 0;
}
