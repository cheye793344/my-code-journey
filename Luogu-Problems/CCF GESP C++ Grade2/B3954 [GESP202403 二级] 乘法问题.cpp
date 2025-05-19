#include<iostream>
using namespace std;

int main() {
    int n; cin >> n; int a; int result = 1; int times = 1;
    while (cin >> a && times <= n) {
        result *= a;
        times++;
    }
    if (result > 1000000) { cout << ">1000000"; }
    else cout << result;
    return 0;
}