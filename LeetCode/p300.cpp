class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> minl;
        for (int x : nums) {
            auto it = lower_bound(minl.begin(), minl.end(), x);
            if (it == minl.end())
                minl.push_back(x);
            else
                *it = min(*it, x);
        }
        return minl.size();
    }
};
