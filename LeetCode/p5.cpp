class Solution {
public:
    string prepare(const string& s) {
        string res;
        res.push_back(-3);
        res.push_back(-1);
        for (char c : s) {
            res.push_back(c);
            res.push_back(-1);
        }
        res.push_back(-2);
        return res;
    }

    pair<int, int> manachar(string s) {
        s = prepare(s);
        vector<int> p(s.length());
        for (int i = 1, mx = 0, id; i < s.length() - 1; ++i) {
            if (mx > i) p[i] = min(p[2 * id - i], mx - i);
            else p[i] = 1;
            while (s[i - p[i]] == s[i + p[i]]) ++p[i];
            if (i + p[i] > mx) {
                id = i;
                mx = i + p[i];
            }
        }
        
        int id = 0;
        for (int i = 1; i < s.length() - 1; ++i)
            if (p[i] > p[id]) id = i;
        return make_pair((id - p[id] + 1) / 2, p[id] - 1);
    }

    string longestPalindrome(string s) {
        auto res = manachar(s);
        return s.substr(res.first, res.second);
    }
};
