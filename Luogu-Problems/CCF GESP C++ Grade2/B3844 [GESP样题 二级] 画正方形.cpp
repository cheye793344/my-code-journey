#include<iostream>
using namespace std;

int main() {
    int n; cin >> n; char target;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            if ('A' + i + j <= 90) {
                target = 'A' + i + j;
            }
            else { target = 'A' + (i + j) % 26; }
            cout << target;
        }
        cout << endl;
    }
    return 0;
}