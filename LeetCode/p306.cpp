class Solution {
public:
    bool isAdditiveNumber(string num) {
        for (size_t i = 1; i < num.size(); ++i) {
            for (size_t j = i + 1; j < num.size(); ++j) {
                if (check(num.substr(0, i), num.substr(i, j - i), num.substr(j)))
                    return true;
            }
        }
        return false;
    }
    
    bool validStr(const string& s) {
        return !(s.size() > 1 && s.front() == '0');
    }
    
    bool check(const string& a, const string& b, const string& c) {
        if (!validStr(a) || !validStr(b))
            return false;
        string res = add(a, b);
        if (res.size() <= c.size() && res == c.substr(0, res.size())) {
            return res.size() == c.size() || check(b, res, c.substr(res.size()));
        }
        return false;
    }
    
    string add(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        string res;
        int carry = 0, alen = a.size(), blen = b.size();
        for (int i = 0, ed = max(alen, blen); i < ed; ++i) {
            carry += i < alen ? a[i] - '0' : 0;
            carry += i < blen ? b[i] - '0' : 0;
            res.push_back(carry % 10 + '0');
            carry /= 10;
        }
        if (carry)
            res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};
