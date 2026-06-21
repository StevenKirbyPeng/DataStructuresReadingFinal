#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<int> dfn, low, parent;
vector<bool> isArticulation;
int timer = 0;

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    int childCount = 0;

    for (int v : graph[u]) {
        if (dfn[v] == 0) {
            parent[v] = u;
            childCount++;
            dfs(v);
            low[u] = min(low[u], low[v]);

            // 非 root：若 child 無法經 back edge 回到 u 的祖先，u 是 articulation point
            if (parent[u] != -1 && low[v] >= dfn[u]) {
                isArticulation[u] = true;
            }
        } else if (v != parent[u]) {
            // back edge
            low[u] = min(low[u], dfn[v]);
        }
    }

    // root 若有兩個以上 DFS child，就是 articulation point
    if (parent[u] == -1 && childCount > 1) {
        isArticulation[u] = true;
    }
}

int main() {
    graph = {
        {1},
        {0, 2, 3},
        {1},
        {1, 4, 5},
        {3},
        {3}
    };

    int n = graph.size();
    dfn.assign(n, 0);
    low.assign(n, 0);
    parent.assign(n, -1);
    isArticulation.assign(n, false);

    dfs(0);

    cout << "vertex dfn low articulation\n";
    for (int i = 0; i < n; i++) {
        cout << i << "      " << dfn[i] << "   " << low[i] << "   "
             << (isArticulation[i] ? "yes" : "no") << "\n";
    }
    return 0;
}
