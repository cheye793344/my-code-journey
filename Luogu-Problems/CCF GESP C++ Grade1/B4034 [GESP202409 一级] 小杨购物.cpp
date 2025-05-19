#include<iostream>
using namespace std;

int main() {
    int money;
    int a, b;
    cin >> money >> a >> b;
    int result = money / (a + b);
    cout << result;
    return 0;
}