#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// ¼ì²é
bool check(long long max_cost, const vector<int>& a) {
    // Ì°ÐÄ
    long long prev_B = (long long)a[0] - max_cost;

    for (size_t i = 1; i < a.size(); ++i) {
        long long min_possible = prev_B + 1;
        long long lowest_allowable = (long long)a[i] - max_cost;

        long long current_B = max(min_possible, lowest_allowable);

        if (current_B > (long long)a[i] + max_cost) {
            return false;
        }

        prev_B = current_B;
    }
    return true;
}
void solve() {
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        long long low = 0, high = 2e9;
        long long ans = high;
        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (check(mid, a)) {
                ans = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        cout << ans << "\n";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}