#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    char a[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 'a';
        }
    }
    for (int j = 0; j < n; ++j) {
        a[n / 2][j] = '-';
    }
    for (int i = 0; i < n; ++i) {
        a[i][0] = '|';
        a[i][n - 1] = '|';
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}