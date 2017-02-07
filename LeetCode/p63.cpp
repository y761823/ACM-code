class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        if (grid.empty() || grid.front().empty())
            return 0;
        int n = grid.size(), m = grid.front().size();
        vector<int> pre(m), now(m);
        pre[0] = 1;
        for (int i = 0; i < n; ++i) {
            now[0] = (pre[0] & !grid[i][0]);
            for (int j = 1; j < m; ++j) {
                if (grid[i][j])
                    now[j] = 0;
                else
                    now[j] = pre[j] + now[j - 1];
            }
            swap(pre, now);
        }
        return pre.back();
    }
};
