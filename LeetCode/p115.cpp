class Solution {
public:
    int numDistinct(string s, string t) {
        long dp[2][t.size() + 1];
        memset(dp[0], 0, sizeof(dp[0]));
        int cur = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            dp[cur][0] = 1;
            cur ^= 1;
            for (size_t j = 0; j < t.size(); ++j) {
                dp[cur][j + 1] = dp[cur ^ 1][j + 1];
                if (s[i] == t[j])
                    dp[cur][j + 1] += dp[cur ^ 1][j];
            }
        }
        return dp[cur][t.size()];
    }
};
