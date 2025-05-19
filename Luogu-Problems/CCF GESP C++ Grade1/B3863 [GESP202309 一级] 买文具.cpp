#include<iostream>
using namespace std;

bool is_enough(int a, int b, int c, int money) {
    return money - 2 * a - 5 * b - 3 * c >= 0;
}

int main() {
    int x, y, z;
    int money;
    cin >> x >> y >> z >> money;
    if (is_enough(x, y, z, money)) {
        cout << "Yes" << endl;
        cout << money - 2 * x - 5 * y - 3 * z;
    }
    else {
        cout << "No" << endl;
        cout << 2 * x + 5 * y + 3 * z - money;
    }
    return 0;
}