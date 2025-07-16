#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<bool> isArrived(n, false);
    int num;
    for (int i = 0; i < m; ++i) {
        cin >> num;
        isArrived[num] = true;
    }

    vector<int> missing;
    for (int i = 0; i < n; ++i) {
        if (!isArrived[i]) {
            missing.push_back(i);
        }
    }

    if (missing.empty()) {
        cout << n << endl;
    }
    else {
        for (size_t i = 0; i < missing.size(); ++i) {
            if (i != 0) cout << " ";
            cout << missing[i];
        }
        cout << endl;
    }

    return 0;
}