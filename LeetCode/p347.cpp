class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums)
            cnt[x]++;
        
        vector<int> res;
        for (auto p : cnt)
            res.push_back(p.first);
        
        nth_element(res.begin(), res.begin() + k, res.end(), [&](int l, int r) {
            return cnt[l] > cnt[r];
        });
        res.resize(k);
        return res;
    }
};
