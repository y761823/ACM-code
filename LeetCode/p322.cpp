class Solution {
    void update_max(int& a, int b) {
        if (a == -1 || a > b)
            a = b;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int x : coins) {
            for (int i = x; i <= amount; ++i)
                if (dp[i - x] >= 0) update_max(dp[i], dp[i - x] + 1);
        }
        return dp[amount];
    }
};
