class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res{{}};
        sort(nums.begin(), nums.end());
        for (size_t p = 0; p < nums.size(); ) {
            size_t cnt = 1;
            while (p + cnt < nums.size() && nums[p] == nums[p + cnt])
                cnt++;
            for (size_t i = 0, ed = res.size(); i < ed; ++i) {
                vector<int> vec(res[i]);
                for (size_t k = 0; k < cnt; ++k) {
                    vec.push_back(nums[p]);
                    res.push_back(vec);
                }
            }
            p += cnt;
        }
        return res;
    }
};
