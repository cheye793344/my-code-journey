#include<iostream>
using namespace std;

int main() {
    int n;
    int result = 0;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] % 9 == 0 && a[i] % 8 != 0) { ++result; }
    }
    cout << result;
    return 0;
}