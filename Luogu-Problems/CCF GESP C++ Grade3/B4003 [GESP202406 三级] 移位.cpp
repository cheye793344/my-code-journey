#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<char> alphabet{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
    for (char& c : alphabet) {
        c = 'A' + (c - 'A' + n) % 26;
    }
    for (char& c : alphabet) {
        cout << c;
    }
    return 0;
}