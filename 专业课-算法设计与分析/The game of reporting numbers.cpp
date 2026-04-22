#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int  main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(0); 

	int n; 
	int m; 
	while (cin >> n >> m) {
		vector<int> a(n); 
		for (int i = 0; i < n; ++i) {
			cin >> a[i]; 
		}

		for (int i = 0; i < m; ++i) {
			int q; 
			cin >> q; 
			auto it = upper_bound(a.begin(), a.end(), q);
			if (it == a.begin()) {
				cout << a[0] << (i == m - 1 ? "" : " "); 
			}
			else {
				cout << *(it - 1) << (i == m - 1 ? "" : " "); 
			}
		}
		cout << endl;
	}
	return 0; 
}