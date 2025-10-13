#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    int x = 1;
    x &= a;
    cout << x << endl;
    x |= b;
    cout << x << endl;
    x <<= c;
    cout << x << endl;
    x ^= d;
    cout << x << endl;
    x >>= e;
    cout << x << endl;
    return 0;
}