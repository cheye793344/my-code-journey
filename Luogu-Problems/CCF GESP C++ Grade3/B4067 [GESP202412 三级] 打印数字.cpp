#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    map<char, vector<string>> digitMap = {
        {'0', {
            ".....",
            ".***.",
            ".***.",
            ".***.",
            "....."
        }},
        {'1', {
            "****.",
            "****.",
            "****.",
            "****.",
            "****."
        }},
        {'2', {
            ".....",
            "****.",
            ".....",
            ".****",
            "....."
        }},
        {'3', {
            ".....",
            "****.",
            ".....",
            "****.",
            "....."
        }}
    };

    string num;
    cin >> num;
    vector<string> result(5);

    for (char c : num) {
        for (int i = 0; i < 5; ++i) {
            result[i] += digitMap[c][i];
        }
    }

    for (const string& line : result) {
        cout << line << endl;
    }

    return 0;
}