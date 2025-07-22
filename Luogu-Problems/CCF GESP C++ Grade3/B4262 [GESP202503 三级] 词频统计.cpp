#include <iostream>
#include <map>
#include <cctype>
#include <string>
using namespace std;

string toLowercase(const string& word) {
    string lowerWord;
    for (char s : word) {
        lowerWord += tolower(s);
    }
    return lowerWord;
}

int main() {
    int n; cin >> n;
    map<string, int> wordCount;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        string lowerWord = toLowercase(word);
        wordCount[lowerWord]++;
    }
    string mostFrequentWord;
    int maxCount = 0;
    for (const auto& pair : wordCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentWord = pair.first;
        }
    }
    cout << mostFrequentWord;
    return 0;
}