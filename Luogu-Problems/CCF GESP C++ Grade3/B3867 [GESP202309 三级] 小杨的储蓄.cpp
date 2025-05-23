#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, d;
    cin >> n >> d;

    vector<int> savings(n, 0);

    for (int day = 1; day <= d; day++) {
        int jar;
        cin >> jar;
        savings[jar] += day;
    }

    for (int i = 0; i < n; i++) {
        cout << savings[i];
        if (i < n - 1) cout << " ";
    }

    return 0;
}