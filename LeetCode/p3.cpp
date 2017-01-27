class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        bool exist[128] = {0};
        int res = 0;
        for (int l = 0, r = 0; r < (int)s.size(); ++r) {
            while (exist[s[r]])
                exist[s[l++]] = false;
            exist[s[r]] = true;
            res = max(res, r - l + 1);
        }
        return res;
    }
};
