#include <iostream>
#include <vector>
using namespace std;

// k 元樹表示法中，每個節點固定保留 k 個 child 指標
int countWastedPointers(const vector<int>& degree, int k) {
    int wasted = 0;
    for (int d : degree) {
        wasted += (k - d); // 沒有用到的 child 指標數量
    }
    return wasted;
}

int main() {
    int k = 4;
    vector<int> degree = {3, 2, 0, 1, 0, 0, 0};

    cout << "k = " << k << '\n';
    cout << "Number of nodes = " << degree.size() << '\n';
    cout << "Total child pointer fields = " << k * degree.size() << '\n';
    cout << "Wasted pointer fields = " << countWastedPointers(degree, k) << '\n';
    return 0;
}