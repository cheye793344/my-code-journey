#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float a;
    double b;
    cin >> a >> b;
    cout << fixed << setprecision(10) << a << " " << b << endl;
    return 0;
}