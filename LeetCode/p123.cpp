class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int res1 = 0, res = 0, min1 = prices.front();
        int max2 = -prices.front(), val = prices.front();
        for (int x : prices) {
            res = max(res, x + max2);
            if (x < val)
                max2 = max2 + val - x,
                val = x;
            if (res1 - x > max2)
                max2 = res1 - x,
                val = x;
            res1 = max(res1, x - min1);
            min1 = min(min1, x);
        }
        return res;
    }
};
