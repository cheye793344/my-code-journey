#include <iostream>
using namespace std;

bool isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int daysInMonth(int y, int m) {
    if (m == 2) {
        return isLeapYear(y) ? 29 : 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    }
    return 31;
}

int main() {
    int y, m, d, h, k;
    cin >> y >> m >> d >> h >> k;

    int totalHours = h + k;

    while (totalHours >= 24) {
        d++;
        totalHours -= 24;

        if (d > daysInMonth(y, m)) {
            m++;
            d = 1;

            if (m > 12) {
                y++;
                m = 1;
            }
        }
    }

    h = totalHours;

    cout << y << " " << m << " " << d << " " << h << endl;

    return 0;
}