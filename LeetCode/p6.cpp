class Solution {
public:
    void run(string &res, const string& s, int start, int interval1, int interval2) {
        int i = start, p = 0;
        vector<int> interval {interval1, interval2};
        for (int i = start; i < (int)s.length(); i += interval[p], p ^= 1)
            res.push_back(s[i]);
    }

    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
        string res;
        int cnt = numRows * 2 - 2;
        run(res, s, 0, cnt, cnt);
        for (int i = 1; i < numRows - 1; ++i) {
            run(res, s, i, cnt - 2 * i, 2 * i);
        }
        if (numRows > 1)
            run(res, s, numRows - 1, cnt, cnt);
        return res;
    }
};
