#include <iostream>
#include <math.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        double x;
        cin >> x;
        double result = a * x * x + b * x + c;
        if (fabs(result) <= 1e-6) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}