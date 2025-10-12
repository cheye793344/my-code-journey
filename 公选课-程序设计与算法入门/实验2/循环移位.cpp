#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int num = (i - m + n) % n + 1;
        cout << num;
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}