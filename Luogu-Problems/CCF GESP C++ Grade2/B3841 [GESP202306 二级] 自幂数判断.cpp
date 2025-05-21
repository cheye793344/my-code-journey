#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int num; cin >> num;
        int origin_num = num;
        int sum = 0;
        int temp = num;
        int digits = 0;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }
        while (num > 0) {
            sum += pow((num % 10), digits);
            num /= 10;
        }
        if (sum == origin_num)cout << "T" << endl;
        else cout << "F" << endl;
    }
    return 0;
}