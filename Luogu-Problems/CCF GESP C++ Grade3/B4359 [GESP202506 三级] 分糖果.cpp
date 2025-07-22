#include <iostream>

using namespace std;

int main() {
    int n; cin >> n;
    long long int sum = 0;
    long long int foreCount = 0;
    for (int i = 0; i < n; ++i) {
        long long int count;
        cin >> count;
        if (count > foreCount) {
            sum += count;
            foreCount = count;
        }
        else {
            sum += foreCount + 1;
            foreCount++;
        }
    }
    cout << sum;
}