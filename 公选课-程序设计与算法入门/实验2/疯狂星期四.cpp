#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int T;
    cin >> T;
    cout << fixed << setprecision(2);
    for (int i = 0; i < T; i++) {
        double m;
        cin >> m;
        double result;
        if (m >= 100) {
            result = m * 0.8;
        }
        else if (m >= 50) {
            result = m * 0.9;
        }
        else if (m >= 30) {
            result = m - 5;
        }
        else {
            result = m;
        }
        cout << result << endl;
    }
    return 0;
}