#include<iostream>
using namespace std;

class Time {
    int hour;
    int minute;
public:
    Time(int a, int b) :hour(a), minute(b) {}
    int to_minute() {
        return hour * 60 + minute;
    }
};

int main() {
    int b1, e1, b2, e2;
    cin >> b1 >> b2 >> e1 >> e2;
    Time begin(b1, b2);
    Time end(e1, e2);
    cout << end.to_minute() - begin.to_minute();
    return 0;
}