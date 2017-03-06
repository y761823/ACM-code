class Solution {
public:
    bool isIsomorphic(string s, string t) {
        char match1[128] = {0}, match2[128] = {0};
        for (size_t i = 0; i < s.size(); ++i) {
            if (match1[s[i]] == 0 && match2[t[i]] == 0) {
                match1[s[i]] = t[i];
                match2[t[i]] = s[i];
            } else if (match1[s[i]] != t[i] || match2[t[i]] != s[i])
                return false;
        }
        return true;
    }
};
