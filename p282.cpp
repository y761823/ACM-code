class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        vector<char> ops(num.size());
        
        auto buildStr = [&]() {
            string str;
            for (size_t i = 0; i < num.size(); ++i) {
                if (ops[i])
                    str += ops[i];
                str += num[i];
            }
            return str;
        };
        
        function<void(size_t, long, long, char)> dfs = [&](size_t pos, long val, long pVal, char pOp) {
            if (pos == num.size()) {
                if (val == target)
                    res.push_back(buildStr());
            } else {
                long v = 0;
                size_t ed = num[pos] == '0' ? pos + 1 : num.size();
                for (size_t i = pos; i < ed; ++i) {
                    v = v * 10 + (num[i] - '0');
                    dfs(i + 1, val + v, v, ops[pos] = '+');
                    dfs(i + 1, val - v, v, ops[pos] = '-');
                    
                    ops[pos] = '*';
                    dfs(i + 1,
                        pOp == '+' ? val - pVal + pVal * v : val + pVal - pVal * v,
                        pVal * v,
                        pOp);
                    ops[pos] = 0;
                }
            }
        };
        
        long v = 0;
        for (size_t i = 0; i < num.size(); ++i) {
            v = v * 10 + (num[i] - '0');
            dfs(i + 1, v, v, '+');
            if (v == 0)
                break;
        }
        return res;
    }
};
