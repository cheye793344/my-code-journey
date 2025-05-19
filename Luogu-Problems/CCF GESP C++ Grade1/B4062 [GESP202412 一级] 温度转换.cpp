#include<iostream>
#include<iomanip>
using namespace std;

int main() {
    double k;
    cin >> k;
    if ((k - 273.15) * 1.8 + 32 > 212) { cout << "Temperature is too high!"; }
    else { cout << fixed << setprecision(2) << k - 273.15 << " " << (k - 273.15) * 1.8 + 32; }
    return 0;
}