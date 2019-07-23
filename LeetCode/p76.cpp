class Solution {
public:
    string minWindow(string s, string t) {
        int cnt[128] = {};
        for (char c : t)
            cnt[c]--;
        int bad = count_if(cnt, cnt + 128, bind(less<int>(), placeholders::_1, 0));
        int minp = 0, minl = 0;
        for (int l = 0, r = 0, n = s.size(); r < n; ++r) {
            bad -= (++cnt[s[r]] == 0);
            if (bad == 0) {
                while (l <= r && bad == 0)
                    bad += (--cnt[s[l++]] == -1);
                int newp = l - 1, newl = r - newp + 1;
                if (!minl || newl < minl)
                    minp = newp, minl = newl;
            }
        }
        return s.substr(minp, minl);
    }
};
