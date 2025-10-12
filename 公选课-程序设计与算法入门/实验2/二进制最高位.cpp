#include <iostream>
using namespace std;

int highestBit(long long n) {
    return n == 1 ? 1 : highestBit(n >> 1) + 1;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        long long N;
        cin >> N;
        cout << highestBit(N) << endl;
    }
    return 0;
}