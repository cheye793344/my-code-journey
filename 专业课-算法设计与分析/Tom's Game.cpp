#include <iostream>
#include <vector>
using namespace std;

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(m));
	vector<long long> rowSum(n, 0);
	vector<long long> colSum(m, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            rowSum[i] += a[i][j];
            colSum[j] += a[i][j];
		}
	}
	long long ans = 0; 
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ans < rowSum[i] + colSum[j] - a[i][j]) {
                ans = rowSum[i] + colSum[j] - a[i][j];
		   }
		}
	}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin >> T;
    while (T--) { 
		solve();
	}
	return 0;
}