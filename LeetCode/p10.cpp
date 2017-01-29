class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<char>> dp(n + 1, vector<char>(m + 1));
        dp[0][0] = true;
        for (int i = 0; i < m; ++i) if (p[i] == '*')
            dp[0][i + 1] = dp[0][i - 1];
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (p[j] == '.' || s[i] == p[j]) {
                    dp[i + 1][j + 1] = dp[i][j];
                } else if (p[j] == '*') {
                    if (p[j - 1] != '.' && s[i] != p[j - 1])
                        dp[i + 1][j + 1] = dp[i + 1][j - 1];
                    else
                        dp[i + 1][j + 1] = (dp[i][j] || dp[i + 1][j - 1] || dp[i][j + 1]);
                }
            }
        }
        
        return dp[n][m];
    }
};
