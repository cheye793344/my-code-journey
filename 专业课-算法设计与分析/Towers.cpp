#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double dist(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
double closestPair(vector<Point>& points, int left, int right) {
    if (left >= right) return 1e20;
    if (left + 1 == right) return dist(points[left], points[right]);
    int mid = left + (right - left) / 2;
    double d1 = closestPair(points, left, mid);
    double d2 = closestPair(points, mid + 1, right);
    double d = min(d1, d2);
    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - points[mid].x) < d) {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(), strip.end(), compareY);
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        sort(points.begin(), points.end(), compareX);
        double min_dist = closestPair(points, 0, n - 1);
        int ans = static_cast<int>(min_dist);
        cout << ans << "\n";
    }

    return 0;
}