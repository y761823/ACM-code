class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        int res = 0, minInterval = numeric_limits<int>::max();
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int l = i + 1, r = n - 1; l < r; ++l) {
                if (l > i + 1 && nums[l] == nums[l - 1]) continue;
                while (l < r && nums[i] + nums[l] + nums[r] > target)
                    r--;
                
                if (r + 1 < n && nums[i] + nums[l] + nums[r + 1] - target < minInterval)
                    res = nums[i] + nums[l] + nums[r + 1], minInterval = res - target;
                if (l != r && target - (nums[i] + nums[l] + nums[r]) < minInterval)
                    res = nums[i] + nums[l] + nums[r], minInterval = target - res;
            }
        }
        return res;
    }
};
