class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0, two = 0;
        for (int x : nums) {
            one = (one ^ x) & ~two; // x one two = 100 or 010
            two = (two ^ x) & ~one; // x one two = 100 or 001
        }
        return one;
    }
};
