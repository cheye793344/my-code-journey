#include<iostream>
using namespace std;

int main() {
    int lucky_num;
    int left;
    int right;
    cin >> lucky_num >> left >> right;
    int result = 0;
    for (int i = left; i <= right; ++i) {
        if (i % 10 == lucky_num || i % lucky_num == 0) { result += i; }
    }
    cout << result;
    return 0;
}