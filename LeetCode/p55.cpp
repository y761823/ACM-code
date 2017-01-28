class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty()) return true;
        int last = nums.size() - 1;
        for (int i = nums.size() - 2; i >= 0; --i)
            if (i + nums[i] >= last) last = i;
        return last == 0;
    }
};
