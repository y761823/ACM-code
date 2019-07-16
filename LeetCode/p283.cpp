class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        auto rt = nums.begin();
        for (auto it = nums.begin(); it != nums.end(); ++it)
            if (*it) *rt++ = *it;
        while (rt != nums.end())
            *rt++ = 0;
    }
};
