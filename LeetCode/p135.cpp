class Solution {
public:
    int candy(vector<int>& ratings) {
        int res = 1, lcnt = 1, pre = 1, pretall = 1;
        for (size_t i = 1; i < ratings.size(); ++i) {
            if (ratings[i - 1] > ratings[i]) {
                res += ++lcnt;
                pre = 1;
                res -= (pretall >= lcnt);
            } else if (ratings[i - 1] == ratings[i]) {
                res++;
                pretall = pre = lcnt = 1;
            } else {
                pretall = ++pre;
                res += pre;
                lcnt = 1;
            }
        }
        return res;
    }
};
