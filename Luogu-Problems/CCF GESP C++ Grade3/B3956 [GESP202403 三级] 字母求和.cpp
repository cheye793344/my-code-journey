#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int total = 0;
    for (char c : s) {
        if (islower(c)) {
            total += c - 'a' + 1;
        }
        else {
            total -= c;
        }
    }

    cout << total << endl;
    return 0;
}