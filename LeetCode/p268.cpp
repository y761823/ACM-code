class Solution {
public:
    int missingNumber(vector<int>& nums) {
        size_t n = nums.size(), sum = n * (n + 1) / 2;
        for (int x : nums)
            sum -= x;
        return sum;
    }
};
