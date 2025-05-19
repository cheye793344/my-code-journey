#include<iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int addend = 0;
    int result = 0;
    for (int i = 1; i <= n; ++i) {
        addend += i;
        result += addend;
    }
    cout << result;
    return 0;
}