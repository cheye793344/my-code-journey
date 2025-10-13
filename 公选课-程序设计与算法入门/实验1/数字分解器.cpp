#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    int ge = a % 10;
    int shi = (a / 10) % 10;
    int bai = (a / 100) % 10;
    cout << bai << " " << shi << " " << ge << endl;
    return 0;
}