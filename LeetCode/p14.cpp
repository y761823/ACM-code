class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";
        
        size_t minLen = strs[0].length();
        for (size_t i = 1; i < strs.size(); ++i)
            minLen = min(minLen, strs[i].length());
        
        string res;
        for (size_t i = 0; i < minLen; ++i) {
            char c = strs[0][i];
            for (size_t j = 1; j < strs.size(); ++j)
                if (c != strs[j][i]) return res;
            res += c;
        }
        return res;
    }
};
