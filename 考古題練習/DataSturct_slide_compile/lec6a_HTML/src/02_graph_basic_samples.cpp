#include <iostream>
#include <vector>
using namespace std;

// 使用 adjacency list 示範 undirected graph 與 directed graph 的差異
void addUndirectedEdge(vector<vector<int>>& g, int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

void addDirectedEdge(vector<vector<int>>& g, int u, int v) {
    g[u].push_back(v);
}

void printGraph(const vector<vector<int>>& g, string name) {
    cout << name << "\n";
    for (int i = 0; i < (int)g.size(); i++) {
        cout << i << ": ";
        for (int v : g[i]) cout << v << " ";
        cout << "\n";
    }
}

int main() {
    vector<vector<int>> undirected(4), directed(4);

    addUndirectedEdge(undirected, 0, 1);
    addUndirectedEdge(undirected, 0, 2);
    addUndirectedEdge(undirected, 1, 3);

    addDirectedEdge(directed, 0, 1);
    addDirectedEdge(directed, 1, 2);
    addDirectedEdge(directed, 2, 0);
    addDirectedEdge(directed, 2, 3);

    printGraph(undirected, "Undirected graph adjacency list:");
    printGraph(directed, "Directed graph adjacency list:");
    return 0;
}
