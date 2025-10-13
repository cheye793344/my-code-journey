#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    int x = 0;
    x += a + b;
    cout << x << endl;
    x += c++;
    cout << x << endl;
    x += ++c;
    cout << x << endl;
    x += d / a;
    cout << x << endl;
    x *= d % e;
    cout << x << endl;
    return 0;
}