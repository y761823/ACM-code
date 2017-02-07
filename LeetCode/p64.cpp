class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid.front().empty())
            return 0;
        int n = grid.size(), m = grid.front().size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) if (i | j)
                grid[i][j] = min(i ? grid[i][j] + grid[i - 1][j] : numeric_limits<int>::max(),
                                j ? grid[i][j] + grid[i][j - 1] : numeric_limits<int>::max());
        return grid[n - 1][m - 1];
    }
};
