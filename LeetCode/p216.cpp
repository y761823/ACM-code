class Solution {
    vector<vector<int>> res;
    
    void dfs(int st, int cnt, int sum, vector<int>& v) {
        if (cnt == 0) {
            if (sum == 0) res.push_back(v);
            return ;
        }
        int ed = min(9, sum / cnt);
        if (cnt == 1) st == ed;
        for (int i = st; i <= ed; ++i) {
            v.push_back(i);
            dfs(i + 1, cnt - 1, sum - i, v);
            v.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> tmp;
        dfs(1, k, n, tmp);
        return res;
    }
};
