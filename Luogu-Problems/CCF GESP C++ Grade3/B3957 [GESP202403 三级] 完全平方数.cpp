#include<iostream>
#include<cmath>
using namespace std;

bool is_perfect_square(int x) {
    int sqrt_x = int(sqrt(x));
    return sqrt_x * sqrt_x == x;
}

int main() {
    int n; cin >> n;
    int num[n];
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    int count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = num[i] + num[j];
            if (is_perfect_square(sum)) {
                count++;
            }
        }
    }

    cout << count;

    return 0;
}