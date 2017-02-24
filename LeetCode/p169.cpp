class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int mid = (nums.size() + 1) / 2 - 1;
        nth_element(nums.begin(), nums.begin() + mid, nums.end());
        return nums[mid];
    }
};
