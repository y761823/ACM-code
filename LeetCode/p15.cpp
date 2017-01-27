class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        vector<vector<int>> res;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int l = i + 1, r = n - 1; l < r; ++l) {
                if (l > i + 1 && nums[l] == nums[l - 1]) continue;
                while (l < r && nums[i] + nums[l] + nums[r] > 0)
                    r--;
                if (l != r && nums[i] + nums[l] + nums[r] == 0)
                    res.push_back({nums[i], nums[l], nums[r]});
            }
        }
        return res;
    }
};
