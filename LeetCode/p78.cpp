class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        for (int i = (1 << n) - 1; i >= 0; --i) {
            vector<int> tmp;
            for (int j = 0; j < n; ++j)
                if (i & (1 << j)) tmp.push_back(nums[j]);
            res.push_back(std::move(tmp));
        }
        return res;
    }
};
