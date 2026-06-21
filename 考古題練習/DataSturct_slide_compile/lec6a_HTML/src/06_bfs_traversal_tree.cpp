#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int start, const vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS order: ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        // BFS 會先拜訪同一層的所有鄰居
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                cout << "(discover " << v << " from " << u << ") ";
            }
        }
    }
    cout << "\n";
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1},
        {2}
    };
    bfs(0, graph);
    return 0;
}
