#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int r;
	int c;
	int step;
};

int bfs(int startr, int startc, int n, vector<string>& grid) {
	queue<Node> q;
	vector<vector<bool>> visited(n, vector<bool>(n, false));

	q.push({ startr, startc, 0 });
	visited[startr][startc] = true;
	int dr[] = { -1, 1, 0, 0 };
	int dc[] = { 0, 0, -1, 1 };

	while (!q.empty()) {
		Node current = q.front();
		q.pop();

		if (grid[current.r][current.c] == 'D') {
			return current.step;
		}

		for (int i = 0; i < 4; ++i) {
			int nr = current.r + dr[i];
			int nc = current.c + dc[i];

			if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc] && grid[nr][nc] != '#') {
				visited[nr][nc] = true;
				q.push({ nr, nc, current.step + 1 });
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	while (cin >> n && n != 0) {
		vector<string> grid(n);
		int startr = -1, startc = -1;
		for (int i = 0; i < n; ++i) {
			cin >> grid[i];
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] == 'M') {
					startr = i;
					startc = j;
				}
			}
		}
		cout << bfs(startr, startc, n, grid) << endl;
	}
	return 0;
}