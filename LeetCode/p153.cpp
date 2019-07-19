class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 1, r = nums.size();
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[0] <= nums[mid]) l = mid + 1;
            else r = mid;
        }
        return l < nums.size() ? nums[l] : nums[0];
    }
};
