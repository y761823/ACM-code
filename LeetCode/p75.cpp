class Solution {
public:
    void sortColors(vector<int>& nums) {
        int value[3] = {0};
        for (int x : nums)
            value[x]++;
        auto it = nums.begin();
        for (int i = 0; i < 3; ++i)
            while (value[i]--) *it++ = i;
    }
};
