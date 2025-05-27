#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

int main() {
    unordered_map<string, unordered_map<string, long long>> conversion = {
        {"km", {{"m", 1000}, {"mm", 1000000}}},
        {"m", {{"mm", 1000}}},
        {"kg", {{"g", 1000}, {"mg", 1000000}}},
        {"g", {{"mg", 1000}}}
    };

    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        int x;
        string unit1, eq, question, unit2;
        ss >> x >> unit1 >> eq >> question >> unit2;

        long long result = x * conversion[unit1][unit2];

        cout << x << " " << unit1 << " = " << result << " " << unit2 << endl;
    }

    return 0;
}