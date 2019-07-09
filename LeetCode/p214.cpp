class Solution {
public:
    string shortestPalindrome(string s) {
        n = s.size();
        if (!n)
            return "";
        
        manachar(s);
        int maxp = 1;
        for (int i = 2; i < 2 * n + 2; ++i) {
            int l = (i - p[i] + 1) / 2, r = l + p[i] - 1;
            if (l == 0)
                maxp = max(maxp, r);
        }

        auto it = s.rbegin();
        int cnt = n - maxp;
        string res;
        while (cnt--)
            res.push_back(*it++);
        return res + s;
    }

private:
    void manachar(const string& src) {
        int len = 2 * n + 3;
        char s[len] = {};
        int i = 0;
        s[i++] = '!';
        s[i++] = '@';
        for (char c : src) {
            s[i++] = c;
            s[i++] = '@';
        }
        s[i++] = 0;

        p = new int[len];
        p[0] = 0;
        int mx = 0, id;
        for (i = 1; i < len - 1; ++i) {
            if (mx > i) p[i] = min(p[2 * id - i], mx - i);
            else p[i] = 1;
            while (s[i - p[i]] == s[i + p[i]])
                p[i]++;
            if (i + p[i] > mx) {
                mx = i + p[i];
                id = i;
            }
        }
    }

private:
    int *p;
    int n;
};
