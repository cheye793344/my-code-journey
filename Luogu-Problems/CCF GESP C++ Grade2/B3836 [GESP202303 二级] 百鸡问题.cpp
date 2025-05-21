#include <iostream>
using namespace std;

int main() {
    int x, y, z, n, m;
    cin >> x >> y >> z >> n >> m;

    int result = 0;
    for (int rooster = 0; rooster <= m; ++rooster) {
        for (int hen = 0; hen <= m - rooster; ++hen) {
            int chicken = m - rooster - hen;
            if (chicken % z == 0) {

                if (rooster * x + hen * y + chicken / z == n) {
                    result++;
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}