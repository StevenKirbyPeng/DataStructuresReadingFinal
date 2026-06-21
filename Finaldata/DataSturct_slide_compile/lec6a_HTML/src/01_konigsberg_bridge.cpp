#include <iostream>
#include <vector>
using namespace std;

// 判斷無向圖是否有 Euler trail / Euler circuit
// Euler circuit：所有頂點 degree 都是偶數
// Euler trail：剛好 0 或 2 個奇數 degree 頂點
int main() {
    int n = 4; // 4 塊陸地，抽象成 4 個 vertex
    vector<pair<int,int>> bridges = {
        {0,1}, {0,1}, {0,2}, {0,2}, {0,3}, {1,3}, {2,3}
    };

    vector<int> degree(n, 0); // degree[i] 記錄第 i 個頂點連接幾條邊

    // 每一座橋會讓兩端陸地的 degree 各加 1
    for (auto e : bridges) {
        int u = e.first;
        int v = e.second;
        degree[u]++;
        degree[v]++;
    }

    int oddCount = 0;
    cout << "Königsberg Bridge Problem\n";
    for (int i = 0; i < n; i++) {
        cout << "vertex " << i << " degree = " << degree[i] << "\n";
        if (degree[i] % 2 == 1) oddCount++;
    }

    cout << "odd degree count = " << oddCount << "\n";
    if (oddCount == 0) {
        cout << "Result: has Euler circuit\n";
    } else if (oddCount == 2) {
        cout << "Result: has Euler trail only\n";
    } else {
        cout << "Result: no Eulerian walk\n";
    }
    return 0;
}
