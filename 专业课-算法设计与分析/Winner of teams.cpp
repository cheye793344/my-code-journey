#include <iostream>
#include <vector>
#include <queue>
#include <functional> 
using namespace std;

void solve() {
	int N, M;
	while (cin >> N >> M) {
		vector<vector<int>> adjoin(N + 1); //邻接表
		vector<int> d(N + 1, 0); //入读

		for (int i = 0; i < M; ++i) {
			int u, v;
			cin >> u >> v; //输入对
			adjoin[u].push_back(v); //u连v
			d[v]++; //rudujia1
		}

		priority_queue<int, vector<int>, greater<int>> pq; //youxianduilie
		for (int i = 1; i <= N; ++i) {
			if (d[i] == 0) {
				pq.push(i);
			}
		}

		vector <int> solution;
		while (!pq.empty()) {
			//
			int u = pq.top();
			pq.pop();
			solution.push_back(u);

			//lianjiedexiayigedian--
			for (int v : adjoin[u]) {
				d[v]--;
				if (d[v] == 0) {		//jiancha
					pq.push(v);
				}
			}
		}
		for (int i = 0; i < solution.size(); ++i) {
			cout << solution[i] << (i == solution.size() - 1 ? "" : " ");
		}
		cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	solve();
	return 0;
}
