class Solution {
public:
    int rob(vector<int>& nums) {
        int pre1 = 0, pre2 = 0;
        for (int x : nums) {
            int now = max(pre1, pre2 + x);
            pre2 = pre1;
            pre1 = now;
        }
        return pre1;
    }
};
