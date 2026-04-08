#include <iostream>
#include <vector>
using namespace std;

int ans[11];
int currentn;
int currentc;

void dfs(int r, vector<bool>& c, vector<bool>& d1, vector<bool>& d2) {
	if (r == currentn) {
		currentc++;
		return;
	}
	for (int i = 0; i < currentn; i++) {
		if (!c[i] && !d1[r - i + currentn] && !d2[r + i]) {
			c[i] = d1[r - i + currentn] = d2[r + i] = true;

			dfs(r + 1, c, d1, d2);

			c[i] = d1[r - i + currentn] = d2[r + i] = false;
		}
	}


}

void pre() {
	for (int i = 1; i <= 10; i++) {
		currentn = i;
		currentc = 0;

		vector<bool> c(15, false);
		vector<bool> d1(25, false);
		vector<bool> d2(25, false);

		dfs(0, c, d1, d2);
		ans[i] = currentc;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	pre();
	int n;
	while (cin >> n) {
		cout << ans[n] << endl;
	}
	return 0;
}