class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, int> smap;
        for (string& str : strs) {
            string idx = str;
            sort(idx.begin(), idx.end());
            auto it = smap.find(idx);
            if (it != smap.end()) {
                res[it->second].push_back(str);
            } else {
                smap[idx] = res.size();
                res.push_back({str});
            }
        }
        return res;
    }
};
