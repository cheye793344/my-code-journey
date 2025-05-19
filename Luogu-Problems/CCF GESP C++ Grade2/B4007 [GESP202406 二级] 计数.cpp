#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        int num = i;
        while (num > 0) {
            int digit = num % 10; // ȡ���һλ����
            if (digit == k) {
                result++;
            }
            num /= 10; // ȥ�����һλ
        }
    }

    cout << result << endl;
    return 0;
}