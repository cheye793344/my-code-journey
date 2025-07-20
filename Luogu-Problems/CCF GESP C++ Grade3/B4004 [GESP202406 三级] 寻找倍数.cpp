#include <iostream>
#include <vector>
#include <algorithm>
using namespace std
;

bool findMaxMultipleElement(const vector<int>& nums)
{
    int
        Max = *max_element(nums.begin(), nums.end());
    for (int
        num : nums) {
        if (num != 0 && Max % num != 0) return false
            ;
    }
    return true
        ;
}

int main()
{
    int group; cin
        >> group;
    for (size_t j = 0
        ; j < group; j++) {
        int
            count;
        vector<int
        > nums;
        cin
            >> count;
        for (size_t i = 0
            ; i < count; i++) {
            int
                num;
            cin
                >> num;
            nums.push_back(num);
        }
        //得到每组序列nums
        cout << (findMaxMultipleElement(nums) ? "Yes" : "No") << endl
            ;
    }
    //分组进行
    return 0
        ;
}