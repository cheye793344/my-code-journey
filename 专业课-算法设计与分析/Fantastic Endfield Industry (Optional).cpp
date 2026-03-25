#include<iostream>

using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	int ans = (n * 2 + k - 1) / k;
	if (ans < 2) ans = 2;
    cout << ans << endl;
}

int main() {
	int T; cin >> T;
	while(T--) solve();
}