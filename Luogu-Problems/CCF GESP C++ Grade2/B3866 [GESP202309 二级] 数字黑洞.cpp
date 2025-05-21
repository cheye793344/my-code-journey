#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    string num;
    cin >> num;
    int count = 0;
    while (num != "495") {
        sort(num.begin(), num.end());
        string min_num = num;
        reverse(num.begin(), num.end());
        string max_num = num;
        int max_val = stoi(max_num);
        int min_val = stoi(min_num);
        int diff = max_val - min_val;
        num = to_string(diff);
        if (num.length() < 3) num = string(3 - num.length(), '0') + num;
        count++;
    }
    cout << count << endl;
    return 0;
}