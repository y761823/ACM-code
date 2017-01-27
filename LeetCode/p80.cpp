class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2)
            return (int)nums.size();
        int pos = 2;
        for (int i = 2; i < (int)nums.size(); ++i) {
            if (nums[i] != nums[pos - 2])
                nums[pos++] = nums[i];
        }
        return pos;
    }
};
