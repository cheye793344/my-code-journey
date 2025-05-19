#include<iostream>
using namespace std;

int rectangleSorts(int area) {
    int result = 0;
    for (int i = 1; i * i <= area; ++i) {
        if (area % i == 0) {
            ++result;
        }
    }
    return result;
}

int main() {
    int area;
    cin >> area;
    cout << rectangleSorts(area);
    return 0;
}