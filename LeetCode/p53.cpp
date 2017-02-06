class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0, res = numeric_limits<int>::min();
        for (int x : nums) {
            if (sum < 0)
                sum = 0;
            sum += x;
            if (sum > res)
                res = sum;
        }
        return res;
    }
};
