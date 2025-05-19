#include<iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        if (temp % 10 >= 5) { temp = ((temp / 10) + 1) * 10; }
        else { temp = temp / 10 * 10; }
        a[i] = temp;
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}