#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }
    int count = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            int a = matrix[i][j];
            int b = matrix[i][j + 1];
            int c = matrix[i + 1][j];
            int d = matrix[i + 1][j + 1];
            if (a * d == b * c) {
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}