class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto it1 = lower_bound(nums.begin(), nums.end(), target);
        auto it2 = upper_bound(it1, nums.end(), target);
        if (it1 < it2) return {it1 - nums.begin(), it2 - nums.begin() - 1};
        else return {-1, -1};
    }
};
