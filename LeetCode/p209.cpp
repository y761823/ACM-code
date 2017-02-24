class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = numeric_limits<int>::max();
        for (int l = 0, r = 0, sum = 0; r < nums.size(); ++r) {
            sum += nums[r];
            while (l < r && sum - nums[l] >= s) sum -= nums[l++];
            if (sum >= s && r - l + 1 <= res)
                res = r - l + 1;
        }
        return res < numeric_limits<int>::max() ? res : 0;
    }
};
