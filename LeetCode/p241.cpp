class Solution {
public:
    vector<int> val;
    vector<char> op;
    vector<int> res;
    
    vector<int> diffWaysToCompute(string input) {
        if (input.empty())
            return {};
        
        int cur = 0;
        for (char c : input) {
            if (isdigit(c))
                cur = cur * 10 + (c - '0');
            else {
                val.push_back(cur);
                op.push_back(c);
                cur = 0;
            }
        }
        val.push_back(cur);
        
        return calc(0, val.size() - 1);
    }
    
    vector<int> calc(int l, int r) {
        if (l == r)
            return {val[l]};
        vector<int> res;
        for (int i = l; i < r; ++i) {
            vector<int> va = calc(l, i);
            vector<int> vb = calc(i + 1, r);
            for (int a : va) for (int b : vb) {
                if (op[i] == '+')
                    res.push_back(a + b);
                else if (op[i] == '-')
                    res.push_back(a - b);
                else if (op[i] == '*')
                    res.push_back(a * b);
            }
        }
        return res;
    }
};
