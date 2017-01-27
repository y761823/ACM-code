class Solution {
public:
    int findPivot(const vector<int>& nums) {
        int first = nums.front(), l = 1, r = (int)nums.size();
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] > first) l = mid + 1;
            else r = mid;
        }
        return l;
    }

    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int pivot = findPivot(nums);
        int pos = (target >= nums.front() ?
            lower_bound(nums.begin(), nums.begin() + pivot, target) :
            lower_bound(nums.begin() + pivot, nums.end(), target))
            - nums.begin();
        return pos < (int)nums.size() && target == nums[pos] ? pos : -1;
    }
};
