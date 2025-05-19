#include<iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int result1 = 0;
    int result2 = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2 == 0) { result2++; }
        else result1++;
    }
    cout << result1 << " " << result2;
    return 0;
}