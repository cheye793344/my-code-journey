#include<iostream>
using namespace std;
int main()
{
    long long n, i, j, k;
    cin >> n >> i;
    for (j = 1; ; j++)
    {
        bool flag = true;
        long long ans = j * n + i;
        for (k = 1; k < n; k++)
        {
            if (ans % (n - 1)) { flag = false; break; }
            ans = ans / (n - 1) * n + i;
        }
        if (flag)
        {
            cout << ans;
            return 0;
        }
    }
}