#include<iostream>
using namespace std;

int main() {
    int n; cin >> n; int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            char c = 'A' + count % 26;
            count++;
            cout << c;
        }
        cout << endl;
    }
    return 0;
}