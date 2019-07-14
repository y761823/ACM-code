class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res = nums;
        for (size_t i = 1; i < res.size(); ++i)
            res[i] *= res[i - 1];
        int mul = 1;
        for (int i = res.size() - 1; i > 0; --i) {
            res[i] = res[i - 1] * mul;
            mul *= nums[i];
        }
        if (!res.empty())
            res[0] = mul;
        return res;
    }
};
