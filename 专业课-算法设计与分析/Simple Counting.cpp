
#include <iostream>
#include <string>
using namespace std;

//核心函数
long long count(long long N) {
    string strN = to_string(N);
    int len = strN.size();
    long long rest = 0;

    //统计位数<len的所有合法数
    long long pw = 1;
    for (int k = 1; k < len; k++) {
        rest += 7 * pw;
        pw *= 8;
    }

    //统计恰好len位的合法数
    int same = 1;
    for (int i = 0; i < len && same; i++) {
        int num = strN[i] - '0';
        //当前位比num小的合法数字
        int lo = (i == 0) ? 1 : 0; //第一个数不能是0
        int smallerCount = 0;
        for (int x = lo; x < num; x++) {
            if (x != 4 && x != 7) smallerCount++;
        }
        //smallerCount个选择，后面各有8种
        long long tail = 1;
        for (int j = 0; j < len - 1 - i; j++) tail *= 8;
        rest += smallerCount * tail;

        //当前位num本身是否合法
        if (num == 4 || num == 7) same = 0;
    }
    return rest + same;
}

int main() {
    int n; cin >> n;
    long long N;
while (cin >> N) {
        cout << count(N) << endl; 
    }
    return 0;
}