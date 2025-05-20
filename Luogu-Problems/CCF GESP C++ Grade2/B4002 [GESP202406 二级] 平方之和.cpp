#include<iostream>
using namespace std;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int temp; cin >> temp; bool found = false;
        for (int a = 1; a * a < temp; ++a) {
            for (int b = a; b * b < temp; ++b) {
                if (a * a + b * b == temp) {
                    found = true;
                    break;
                }
            }
            if (found)break;
        }
        cout << (found ? "Yes" : "No") << endl;
    }
    return 0;
}