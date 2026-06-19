#include <bits/stdc++.h>
using namespace std;

// Floyd-Warshall Algorithm
// All-Pairs Shortest Paths：計算任意 i 到任意 j 的最短距離。
// 核心公式：dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

int main() {
    const int INF = 1e8;
    const int n = 4;

    vector<vector<int>> dist = {
        {0,   5,   INF, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    for (int k = 0; k < n; ++k) {
        cout << "Allow intermediate vertex k = " << k << '\n';

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    cout << "  Update dist[" << i << "][" << j << "]: "
                         << (dist[i][j] == INF ? -1 : dist[i][j])
                         << " -> " << dist[i][k] + dist[k][j] << '\n';
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "\nFinal all-pairs shortest distance matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << setw(3) << dist[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}