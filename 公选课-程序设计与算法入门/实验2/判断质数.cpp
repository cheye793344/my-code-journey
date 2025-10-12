#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        int n;
        cin >> n;

        if (n <= 1) {
            cout << "No" << endl;
            continue;
        }

        bool isPrime = true;
        for (int j = 2; j * j <= n; j++) {
            if (n % j == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }

    return 0;
}