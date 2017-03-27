class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        if (grid.empty() || grid.front().empty())
            return 0;
        int n = grid.size(), m = grid.front().size(), cnt = 0, edge = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!grid[i][j]) continue;
                ++cnt;
                edge += (i && grid[i - 1][j]);
                edge += (j && grid[i][j - 1]);
            }
        }
        return 4 * cnt - 2 * edge;
    }
};
