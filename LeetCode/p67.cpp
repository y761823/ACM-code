class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        
        string res;
        res.resize(max(a.size(), b.size()) + 1);
        int c = 0;
        for (size_t i = 0; i < res.size(); ++i) {
            c += (i < a.size() && a[i] == '1') + (i < b.size() && b[i] == '1');
            res[i] = '0' + (c & 1);
            c >>= 1;
        }
        if (res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }
};
