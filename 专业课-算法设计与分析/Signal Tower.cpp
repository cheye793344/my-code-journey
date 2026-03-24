#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int T; cin >> T;
    while (T--)
    {
        int max_covering = 0;
        int n, m, X, R;
        cin >> n >> m >> X >> R;
        int R2 = R * R;
        vector <pair <int, int>> points(X);
        for (int i = 0; i < X; i++) {
            cin >> points[i].first >> points[i].second;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int covering = 0;
                for (auto point : points) {
                    int dx = point.first - i;
                    int dy = point.second - j;
                    if (dx * dx + dy * dy <= R2) {
                        covering++;
                    }
                }
                max_covering = max(max_covering, covering);
            }
        }
        cout << max_covering << endl;
    }

    return 0;
}