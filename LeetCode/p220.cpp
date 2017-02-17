class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<int> st;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = st.lower_bound(max((long long)nums[i] - t, (long long)numeric_limits<int>::min()));
            if (it != st.end() && *it <= (long long)nums[i] + t)
                return true;
            st.insert(nums[i]);
            if (i >= k) st.erase(nums[i - k]);
        }
        return false;
    }
};
