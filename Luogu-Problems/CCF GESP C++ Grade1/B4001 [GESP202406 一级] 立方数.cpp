#include<iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n != 1 && n != 8 && n != 27 && n != 64 && n != 125 && n != 216 && n != 343 && n != 512 && n != 729 && n != 1000) { cout << "No"; }
    else { cout << "Yes"; }
    return 0;
}