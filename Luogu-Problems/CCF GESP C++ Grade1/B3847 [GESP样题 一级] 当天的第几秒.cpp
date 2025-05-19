#include<iostream>
using namespace std;

int secondsCulculator(int a, int b, int c) {
    return a * 3600 + b * 60 + c * 1;
}

int main() {
    int h;
    int m;
    int s;
    int result;
    char period;
    cin >> h >> m >> s >> period;
    result = secondsCulculator(h, m, s);
    if (period == 'P') {
        result += 43200;
    }
    cout << result;
    return 0;
}