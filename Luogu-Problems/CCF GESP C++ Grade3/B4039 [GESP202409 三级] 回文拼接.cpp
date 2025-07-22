#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& s, int begin, int end) {
    while (begin < end) {
        if (s[begin++] != s[end--]) return false;
    }
    return true;
}

bool canSplitIntoTwoPalindromes(const string& s) {
    int n = s.size();
    if (n < 4) return false; // 至少需要4字符才能分成两个长度≥2的子串
    for (int i = 1; i <= n - 2; i++) {
        int len1 = i + 1;       // s[0..i]
        int len2 = n - i - 1;   // s[i+1..n-1]
        if (len1 >= 2 && len2 >= 2) {
            if (isPalindrome(s, 0, i) && isPalindrome(s, i + 1, n - 1)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int T; cin >> T;
    while (T--) {
        string s;
        cin >> s;
        cout << (canSplitIntoTwoPalindromes(s) ? "Yes" : "No") << endl;
    }
    return 0;
}