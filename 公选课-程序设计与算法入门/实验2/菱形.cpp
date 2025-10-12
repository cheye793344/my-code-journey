#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    int mid = n / 2;
    for (int i = 0; i < n; i++) {
        int spaces = abs(i - mid);
        int stars = n - 2 * spaces;
        for (int j = 0; j < spaces; j++) {
            cout << " ";
        }
        for (int j = 0; j < stars; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}