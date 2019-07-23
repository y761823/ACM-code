class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        const int MAX = 255;
        vector<string> res;
        int n = s.size();
        auto isValid = [=](const string& str) {
            int val = stoi(str);
            return val < 256 && !(str.size() > 1 && str.front() == '0');
        };
        for (int a = 1; a <= 3 && a < n; ++a) {
            string sa = s.substr(0, a);
            if (!isValid(sa))
                continue;
            for (int b = 1; b <= 3 && a + b < n; ++b) {
                string sb = s.substr(a, b);
                if (!isValid(sb))
                    continue;
                for (int c = 1; c <= 3 && a + b + c < n; ++c) {
                    int d = n - a - b - c;
                    if (d > 3)
                        continue;
                    string sc = s.substr(a + b, c);
                    if (!isValid(sc))
                        continue;
                    string sd = s.substr(a + b + c, d);
                    if (!isValid(sd))
                        continue;
                    res.push_back(sa + '.' + sb + '.' + sc + '.' + sd);
                }
            }
        }
        return res;
    }
};
