#include <iostream>

using namespace std;

int main()
{
	int T; cin >> T;
    while(T--)
    {
        long long x, y; 
        cin >> x >> y;
        if (y == 0) {
            cout << "No" << endl;
            continue;
        }
        if (y == 1) {
            cout << (x == 0 ? "Yes" : "No") << endl;
            continue;
        }
        long long diff = x - (y - 1);
        if (diff >= 0 && diff % 2 == 0) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
	return 0;
}