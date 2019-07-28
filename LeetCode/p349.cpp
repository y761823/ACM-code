class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set;
        for (int x : nums1)
            set.insert(x);
        vector<int> res;
        for (int x : nums2) {
            auto it = set.find(x);
            if (it != set.end()) {
                res.push_back(x);
                set.erase(it);
            }
        }
        return res;
    }
};
