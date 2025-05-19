#include<iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    char a[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = 'x';
        }
    }
    for (int i = 0; i < N; i += N / 2) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = '-';
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; j += (N - 1)) {
            a[i][j] = '|';
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << a[i][j];
        }
        cout << endl;
    }
}