#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int to;
    int weight;
};

int main() {
    int n = 4;
    vector<vector<Edge>> graph(n);

    graph[0].push_back({1, 10});
    graph[0].push_back({2, 30});
    graph[1].push_back({2, 5});
    graph[1].push_back({3, 20});
    graph[2].push_back({3, 7});

    cout << "Weighted network adjacency list:\n";
    for (int u = 0; u < n; u++) {
        cout << u << ": ";
        for (Edge e : graph[u]) {
            cout << "(" << e.to << ", w=" << e.weight << ") ";
        }
        cout << "\n";
    }

    int pathCost = 10 + 5 + 7; // path: 0 -> 1 -> 2 -> 3
    cout << "cost of path 0->1->2->3 = " << pathCost << "\n";
    return 0;
}
