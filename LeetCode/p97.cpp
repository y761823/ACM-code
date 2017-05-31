class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= n1; ++i) {
            for (int j = 0; j <= n2; ++j) if (dp[i][j]) {
                if (i < n1 && s1[i] == s3[i + j])
                    dp[i + 1][j] = true;
                if (j < n2 && s2[j] == s3[i + j])
                    dp[i][j + 1] = true;
            }
        }
        return dp[n1][n2];
    }
};
