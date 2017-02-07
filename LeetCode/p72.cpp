class Solution {
public:
    void update_min(int &a, int b) {
        if (a > b) a = b;
    }

    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, numeric_limits<int>::max()));
        dp[0][0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (i < n) update_min(dp[i + 1][j], dp[i][j] + 1);
                if (j < m) update_min(dp[i][j + 1], dp[i][j] + 1);
                if (i < n && j < m)
                    update_min(dp[i + 1][j + 1], dp[i][j] + (word1[i] != word2[j]));
            }
        }
        return dp[n][m];
    }
};
