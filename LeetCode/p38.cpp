class Solution {
public:
    string trans(string str) {
        int i = 0, n = (int)str.size();
        string res;
        while (i < n) {
            int cnt = 1;
            while (i + cnt < n && str[i] == str[i + cnt]) ++cnt;
            res += to_string(cnt);
            res.push_back(str[i]);
            i += cnt;
        }
        return res;
    }

    string countAndSay(int n) {
        string res = "1";
        for (int i = 2; i <= n; ++i) {
            res = trans(res);
        }
        return res;
    }
};
