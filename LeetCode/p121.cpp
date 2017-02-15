class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int minp = prices.front(), res = 0;
        for (int x : prices) {
            res = max(res, x - minp);
            minp = min(minp, x);
        }
        return res;
    }
};
