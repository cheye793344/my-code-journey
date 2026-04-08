#include <iostream> 
#include <vector>
#include <string>

using namespace std;

int w, h;
int rcount;

void dfs(int r, int c, vector<string>& grid) {
	if (r < 0 || r >= h || c < 0 || c >= w) return;

	if (grid[r][c] == 'R')return;

	rcount++;
	grid[r][c] = 'R';

	int dr[] = { -1, 0, 1, 0 };
	int dc[] = { 0, 1, 0, -1 };
	for (int i = 0; i < 4; ++i) {
		dfs(r + dr[i], c + dc[i], grid);
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (cin >> w >> h) {
		vector<string> grid(h);
		int startr, startc = -1;

		for (int i = 0; i < h; ++i) {
			cin >> grid[i];
			for (int j = 0; j < w; ++j) {
				if (grid[i][j] == 'G') {
					startr = i;
					startc = j;
				}
			}
		}
		rcount = 0;

		if (startc != -1 && startr != -1) dfs(startr, startc, grid);

		cout << rcount << endl;
	}
	return 0;
}