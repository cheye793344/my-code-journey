#include<iostream>
using namespace std;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int num; cin >> num;
        int digits_sum = 0;
        while (num > 0) {
            digits_sum += num % 10;
            num = num / 10;
        }
        if (digits_sum % 7 == 0) {
            cout << "Yes" << endl;
        }
        else cout << "No" << endl;
    }
    return 0;
}