#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int num) {
    if (num <= 1)return false;
    if (num == 2)return true;
    if (num > 2) {
        if (num % 2 == 0)return false;
        for (int i = 3; i <= sqrt(num); i += 2) {
            if (num % i == 0)return false;
        }
        return true;
    }
}

int main() {
    int a, b; cin >> a >> b; int result = 0;
    for (int i = a; i <= b; ++i) {
        if (isPrime(i))result++;
    }
    cout << result;
    return 0;
}