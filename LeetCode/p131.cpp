class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        if (!n)
            return {};
        
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int l = 0; l < n; ++l)
            for (int i = 0; i + l < n; ++i)
                isPal[i][i + l] = (s[i] == s[i + l] && (l < 2 || isPal[i + 1][i + l - 1]));
        
        vector<vector<vector<string>>> res(n);
        vector<bool> vis(n);
        function<void(int)> dfs = [&](int pos) {
            if (pos >= n || vis[pos])
                return ;
            vis[pos] = true;
            
            for (int i = pos + 1; i <= n; ++i) {
                if (isPal[pos][i - 1]) {
                    string cur = s.substr(pos, i - pos);
                    if (i == n) {
                        res[pos].push_back({cur});
                    } else {
                        dfs(i);
                        for (const vector<string>& vec : res[i]) {
                           vector<string> t {cur};
                           t.insert(t.end(), vec.begin(), vec.end());
                           res[pos].push_back(t);
                        }
                    }
                }
            }
        };
        dfs(0);
        return res[0];
    }
};
