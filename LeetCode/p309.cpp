class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int hold = -*max_element(prices.begin(), prices.end()), cd = 0, free = 0;
        for (int x : prices)
        {
            int newHold = max(hold, free - x);
            int newCd = hold + x;
            int newFree = max(cd, free);
            hold = newHold;
            cd = newCd;
            free = newFree;
        }
        return max(free, cd);
    }
};
