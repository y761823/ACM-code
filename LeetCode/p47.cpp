class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res {nums};
        while (next_permutation(nums.begin(), nums.end()))
            res.push_back(nums);
        return res;
    }
};
