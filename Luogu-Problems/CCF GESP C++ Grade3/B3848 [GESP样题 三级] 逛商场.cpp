#include<iostream>
#include<queue>
using namespace std;

int main() {
    int n; cin >> n; int result = 0; queue<int> prices;
    for (int i = 0; i < n; ++i) {
        int price;
        cin >> price;
        prices.push(price);
    }
    int money; cin >> money;
    while (!prices.empty()) {
        if (money >= prices.front()) {
            money -= prices.front();
            prices.pop();
            result++;
        }
        else prices.pop();
    }
    cout << result;
    return 0;
}