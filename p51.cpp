class Solution {
public:
    vector<int> col, counter, diagonal;
    vector<vector<string>> res;

    void dfs(int r, int n, vector<string>& now) {
        if (r == n) return res.push_back(now);
        for (int c = 0; c < n; ++c) {
            int &x = col[c], &y = diagonal[r + c], &z = counter[r + n - c - 1];
            if (x || y || z) continue;
            x = y = z = true;
            now[r][c] = 'Q';
            dfs(r + 1, n, now);
            now[r][c] = '.';
            x = y = z = false;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        col.resize(n);
        counter.resize(2 * n + 1);
        diagonal.resize(2 * n + 1);
        vector<string> now(n, string(n, '.'));
        dfs(0, n, now);
        return res;
    }
};
