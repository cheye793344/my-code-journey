#include <iostream>
#include <string>
using namespace std;

string decimalToRBase(int N, int R) {
    string result = "";
    while (N > 0) {
        int remainder = N % R;
        if (remainder < 10) {
            result = char('0' + remainder) + result;
        }
        else {
            result = char('A' + remainder - 10) + result;
        }
        N = N / R;
    }
    return result;
}

int main() {
    int N, R;
    cin >> N >> R;
    cout << decimalToRBase(N, R) << endl;
    return 0;
}