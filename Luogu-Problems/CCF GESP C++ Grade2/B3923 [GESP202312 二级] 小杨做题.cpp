#include<iostream>
using namespace std;

int main() {
    int a, b, m, N;
    cin >> a >> b >> m >> N;
    int total = a + b;
    int date = 3;
    int past1 = a;
    int past2 = b;
    int today;
    while (today < m && date <= N) {
        today = past1 + past2;
        total = total + today;
        date++;
        past1 = past2;
        past2 = today;
    }
    cout << total;
    return 0;
}