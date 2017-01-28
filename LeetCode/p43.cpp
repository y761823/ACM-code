class Solution {
public:
    string multiply(string num1, string num2) {
        int a = num1.size(), b = num2.size(), c = a + b;
        
        vector<int> res(c, 0);
        for (int i = 0; i < a; ++i)
            for (int j = 0; j < b; ++j)
                res[i + j] += (num1[a - i - 1] - '0') * (num2[b - j - 1] - '0');
        for (int i = 0; i < c - 1; ++i)
            res[i + 1] += res[i] / 10, res[i] = res[i] % 10;
        
        while (res.size() > 1 && !res.back()) res.pop_back();
        reverse(res.begin(), res.end());
        
        string ans(res.size(), 0);
        for (size_t i = 0; i < res.size(); ++i)
            ans[i] = res[i] + '0';
        return ans;
    }
};
