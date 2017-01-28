class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i)
            while (0 < nums[i] && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
        int res = 0;
        while (res < nums.size() && nums[res] == res + 1)
            res++;
        return res + 1;
    }
};
