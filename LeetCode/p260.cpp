class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int p = 0;
        for (int x : nums)
            p ^= x;
        p = (p & -p);
        
        int a = 0, b = 0;
        for (int x : nums)
            (x & p ? a : b) ^= x;
        return {a, b};
    }
};
