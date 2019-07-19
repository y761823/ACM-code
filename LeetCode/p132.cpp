class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        if (!n)
            return {};
        
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int l = 0; l < n; ++l)
            for (int i = 0; i + l < n; ++i)
                isPal[i][i + l] = (s[i] == s[i + l] && (l < 2 || isPal[i + 1][i + l - 1]));
        
        vector<int> minc(n + 1, -1);
        minc[n] = 0;
        function<void(int)> dfs = [&](int pos) {
            if (pos >= n || minc[pos] >= 0)
                return ;
            int& res = minc[pos] = n - 1;
            
            for (int i = n; i > pos; --i) {
                if (isPal[pos][i - 1]) {
                    if (i == n) {
                        res = 0;
                        break;
                    } else {
                        dfs(i);
                        res = min(res, minc[i] + 1);
                    }
                }
            }
        };
        dfs(0);
        return minc[0];
    }
};
