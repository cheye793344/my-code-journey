#include<iostream>
using namespace std;

int main() {
    int h, m, s, k;
    cin >> h >> m >> s >> k;
    int begin = h * 3600 + m * 60 + s;
    int end = begin + k;
    cout << end / 3600 << " " << end % 3600 / 60 << " " << end % 60;
    return 0;
}