class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2)
            return true;
        int cnt[26] = {};
        for (size_t i = 0; i < s1.size(); ++i) {
            cnt[s1[i] - 'a']++;
            cnt[s2[i] - 'a']--;
        }
        if (count(cnt, cnt + 26, 0) != 26)
            return false;
        for (size_t i = 1; i < s1.size(); ++i) {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) &&
                isScramble(s1.substr(i), s2.substr(i)))
                return true;
            if (isScramble(s1.substr(0, i), s2.substr(s1.size() - i)) &&
                isScramble(s1.substr(i), s2.substr(0, s1.size() - i)))
                return true;
        }
        return false;
    }
};
