#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int total = 0;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        total += __builtin_popcount(num);
    }
    cout << total << " " << (total % 2) << endl;
    return 0;
}