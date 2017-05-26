class Solution {
    bool islegal(char c) {
        return isdigit(c) && c != '0';
    }
    bool islegal(char c1, char c2) {
        if (isdigit(c1) && isdigit(c2)) {
            int x = (c1 - '0') * 10 + (c2 - '0');
            return 10 <= x && x <= 26;
        }
        return false;
    }
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        int pre2 = 0, pre1 = 1;
        char prec = '0';
        for (char c : s) {
            int now = 0;
            if (islegal(c))
                now += pre1;
            if (islegal(prec, c))
                now += pre2;
            pre2 = pre1;
            pre1 = now;
            prec = c;
        }
        return pre1;
    }
};
