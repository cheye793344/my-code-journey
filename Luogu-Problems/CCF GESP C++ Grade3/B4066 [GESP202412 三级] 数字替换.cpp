#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> sequence;
    vector<int> temp;
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        sequence.push_back(c);
        temp.push_back(c);
    }
    sort(temp.begin(), temp.end());
    int max_val, min_val;
    min_val = temp.front();
    max_val = temp.back();
    for (int& c : sequence) {
        if (c < k) {
            c = min_val;
        }
        else if (c > k) {
            c = max_val;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i < n - 1)cout << sequence[i] << " ";
        if (i == n - 1)cout << sequence[i];
    }
    return 0;
}