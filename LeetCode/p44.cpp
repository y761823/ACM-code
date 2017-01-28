class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size() + 1, m = p.size() + 1;
        s = "aa" + s, p = "aa" + p;
        vector<vector<bool>> dp(s.size(), vector<bool>(p.size()));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j] == '*') {
                    dp[i][j] = (dp[i - 1][j - 1] || dp[i - 1][j] || dp[i][j - 1]);
                } else {
                    dp[i][j] = (s[i] == p[j] && dp[i - 1][j - 1]);
                }
            }
        }
        return dp[n][m];
    }
};
