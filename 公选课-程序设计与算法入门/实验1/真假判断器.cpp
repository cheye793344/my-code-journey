#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    bool x;
    x = a > b;
    cout << x << endl;
    x = !(a == b);
    cout << x << endl;
    x = (a + b > 0) && (a - b > 0);
    cout << x << endl;
    return 0;
}