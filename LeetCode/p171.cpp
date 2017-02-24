class Solution {
public:
    int titleToNumber(string s) {
        int res = 0, p = 1;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            res += (*it - 'A' + 1) * p;
            p *= 26;
        }
        return res;
    }
};
