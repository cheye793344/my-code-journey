#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int target;
        cin >> target;
        double fourthRoot = round(pow(target, 1.0 / 4));
        if (static_cast<int> (pow(fourthRoot, 4)) == target) {
            cout << fourthRoot << endl;
        }
        else {
            cout << "-1" << endl;
        }
    }
    return 0;
}