#include<iostream>
using namespace std;

int main() {
    int beg;
    int end;
    int n = 0;

    cin >> beg >> end;
    for (int i = beg + 1; i < end; ++i) {
        if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) { n += i; }
    }
    cout << n;
    return 0;
}