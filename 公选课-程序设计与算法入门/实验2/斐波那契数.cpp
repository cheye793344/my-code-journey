#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int T;
    cin >> T;
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(1);
    while (true) {
        long long next = fib[fib.size() - 1] + fib[fib.size() - 2];
        if (next > 9000000000000000000LL) {
            break;
        }
        fib.push_back(next);
    }
    unordered_set<long long> fibSet(fib.begin(), fib.end());
    for (int i = 0; i < T; i++) {
        long long x;
        cin >> x;
        if (fibSet.count(x)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}