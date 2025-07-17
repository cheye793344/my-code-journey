#include<iostream>
#include<vector>
#include<string>
#include<cctype>

using namespace std;

bool isValidPassword(const string& s) {
    //判断长度是否符合要求
    int len = s.size();
    if (len < 6 || len > 12)return false;
    //判断字符是否合法
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    for (char c : s) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else if (c == '!' || c == '@' || c == '#' || c == '$') hasSpecial = true;
        else return false;
    }
    int typeCount = (hasLower ? 1 : 0) + (hasUpper ? 1 : 0) + (hasDigit ? 1 : 0);
    if (typeCount < 2)return false;
    if (!hasSpecial)return false;
    return true;
}
//分离字符串
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    for (char c : s) {
        if (c == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else { token += c; }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}
int main() {
    string line
        ;
    getline(cin, line);
    vector
        <string> passwords = split(line, ',');
    for (const string& pwd : passwords) {
        if (isValidPassword(pwd)) {
            cout
                << pwd << endl;
        }
    }
    return 0;
}