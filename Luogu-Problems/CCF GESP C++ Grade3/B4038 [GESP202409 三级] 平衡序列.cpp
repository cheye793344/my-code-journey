#include <iostream>
#include <vector>

using namespace std;

bool isBalanced(const vector<int>& nums) {
    int total_sum = 0;
    for (int num : nums) {
        total_sum += num;
    }
    if (total_sum % 2 != 0) {
        return false;
    }
    int target = total_sum / 2;
    int running_sum = 0;
    for (int num : nums) {
        running_sum += num;
        if (running_sum == target) {
            return true;
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }
        if (isBalanced(nums)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}