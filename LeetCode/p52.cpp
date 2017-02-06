class Solution {
public:
    vector<int> col, counter, diagonal;
    int res;

    void dfs(int r, int n) {
        if (r == n) {
            res++;
            return ;
        }
        for (int c = 0; c < n; ++c) {
            int &x = col[c], &y = diagonal[r + c], &z = counter[r + n - c - 1];
            if (x || y || z) continue;
            x = y = z = true;
            dfs(r + 1, n);
            x = y = z = false;
        }
    }

    int totalNQueens(int n) {
        col.resize(n);
        counter.resize(2 * n + 1);
        diagonal.resize(2 * n + 1);
        dfs(0, n);
        return res;
    }
};
