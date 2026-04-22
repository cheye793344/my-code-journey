#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	if (!(cin >> t)) return 0;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		nth_element(a.begin(), a.begin() + n / 2, a.end());
		cout << a[n / 2] << "\n";
	}
	return 0;
}