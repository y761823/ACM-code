class Solution {
public:
    int longestSubstring(string s, int k) {
        int cnt[26] = {}, n = s.size();
        for (char c : s)
            cnt[c - 'a']++;
        
        bool anybreak = false;
        for (int i = 0; i < 26; ++i)
            if (cnt[i] != 0 && cnt[i] < k)
                anybreak = true;
        
        if (!anybreak)
            return n;
        
        int res = 0, l = 0;
        while (l < n) {
            while (l < n && !(cnt[s[l] - 'a'] == 0 || cnt[s[l] - 'a'] >= k))
                l++;
            int r = l + 1;
            while (r < n && (cnt[s[r] - 'a'] == 0 || cnt[s[r] - 'a'] >= k))
                r++;
            if (l < n)
                res = max(res, longestSubstring(s.substr(l, r - l), k));
            l = r;
        }
        return res;
    }
};
