#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int n; cin >> n; int result = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = a; b <= n; ++b) {
            int c = sqrt(a * a + b * b);
            if (c > n || c * c != a * a + b * b)continue;
            result++;
        }
    }
    cout << result;
    return 0;
}