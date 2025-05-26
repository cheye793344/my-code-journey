#include <iostream>
#include <unordered_set>
#include <cctype>

using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_set<char> valid_hex = { 'A', 'B', 'C', 'D', 'E', 'F' };
    for (int i = 0; i < n; i++) {
        string num;
        cin >> num;
        bool binary = true, octal = true, decimal = true, hexa = true;
        for (char c : num) {
            if (isdigit(c)) {
                int val = c - '0';
                if (val > 1) binary = false;
                if (val > 7) octal = false;
                if (val > 9) decimal = false;
            }
            else if (isalpha(c)) {
                if (!valid_hex.count(toupper(c))) {
                    binary = octal = decimal = hexa = false;
                    break;
                }
                else {
                    binary = octal = decimal = false;
                }
            }
            else {
                binary = octal = decimal = hexa = false;
                break;
            }
        }
        cout << binary << " " << octal << " " << decimal << " " << hexa << endl;
    }
    return 0;
}