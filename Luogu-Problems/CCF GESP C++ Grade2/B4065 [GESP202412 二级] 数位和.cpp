#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n; cin >> n; int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        string num;
        cin >> num;
        int current_sum = 0;
        for (char c : num) {
            current_sum += c - '0';
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    cout << max_sum;
    return 0;
}