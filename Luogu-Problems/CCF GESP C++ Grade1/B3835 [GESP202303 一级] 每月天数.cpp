#include<iostream>
using namespace std;

class Month {
    int year;
    int month;
public:
    Month(int a, int b) :year(a), month(b) {}
    int days_in_the_month() {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) { return 31; }
        if (month == 4 || month == 6 || month == 9 || month == 11) { return 30; }
        if (month == 2) {
            if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) { return 29; }
            return 28;
        }
    }
};

int main() {
    int y, m;
    cin >> y >> m;
    Month month(y, m);
    cout << month.days_in_the_month();
    return 0;
}