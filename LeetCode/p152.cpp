class Solution {
    typedef vector<int>::iterator Iter;
public:
    static bool isNegative(int x) { return x < 0; };

    int getRes(Iter st, Iter ed) {
        int cnt = count_if(st, ed, isNegative);
        if (cnt & 1) {
            int res = *st;
            auto first = find_if(st, ed, isNegative);
            if (first + 1 < ed)
                res = max(res, accumulate(first + 1, ed, 1, multiplies<int>()));
            auto last = ed - 1;
            while (last != st && *last > 0) --last;
            if (st < last)
                res = max(res, accumulate(st, last, 1, multiplies<int>()));
            return res;
        } else
            return accumulate(st, ed, 1, multiplies<int>());
    }

    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        int res = *max_element(nums.begin(), nums.end());
        auto st = nums.begin();
        while (st != nums.end()) {
            while (st != nums.end() && !*st) ++st;
            auto ed = st;
            while (ed != nums.end() && *ed) ++ed;
            if (st != ed)
                res = max(res, getRes(st, ed));
            st = ed;
        }
        return res;
    }
};
