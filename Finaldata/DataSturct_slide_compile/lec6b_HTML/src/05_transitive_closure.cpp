#include <bits/stdc++.h>
using namespace std;

// Warshall Algorithm for Transitive Closure
// reach[i][j] = true 表示 i 可以到達 j。
// 核心公式：reach[i][j] = reach[i][j] OR (reach[i][k] AND reach[k][j])

int main() {
    const int n = 4;

    vector<vector<int>> reach = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };

    for (int i = 0; i < n; ++i) {
        reach[i][i] = 1; // reflexive closure: each vertex reaches itself
    }

    for (int k = 0; k < n; ++k) {
        cout << "Use intermediate vertex k = " << k << '\n';

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int oldValue = reach[i][j];
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);

                if (!oldValue && reach[i][j]) {
                    cout << "  reach[" << i << "][" << j
                         << "] becomes 1 because "
                         << i << " -> " << k << " and "
                         << k << " -> " << j << '\n';
                }
            }
        }
    }

    cout << "\nTransitive closure matrix:\n";
    for (const auto& row : reach) {
        for (int x : row) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}