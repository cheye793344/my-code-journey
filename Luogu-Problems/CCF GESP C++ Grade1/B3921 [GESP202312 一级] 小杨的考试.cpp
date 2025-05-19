#include<iostream>
using namespace std;

int  main() {
    int begin;
    int elapse;
    cin >> begin >> elapse;
    int result = begin + elapse % 7;
    if (result < 8)
        cout << result;
    else cout << result - 7;
    return 0;
}