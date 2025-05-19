#include<iostream>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    int remained;
    if (y % x == 0) { remained = n - y / x; }
    else { remained = n - y / x - 1; }
    cout << remained;
    return 0;
}