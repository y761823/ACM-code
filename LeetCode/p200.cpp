class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid.front().empty())
            return 0;
        int n = grid.size(), m = grid.front().size();
        
        auto bfs = [&](int r, int c) {
            static const int fr[] = {0, 1, 0, -1};
            static const int fc[] = {1, 0, -1, 0};
            
            queue<int> que;
            que.push(r); que.push(c);
            grid[r][c] = '0';
            while (!que.empty()) {
                r = que.front(); que.pop();
                c = que.front(); que.pop();
                for (int f = 0; f < 4; ++f) {
                    int nr = r + fr[f], nc = c + fc[f];
                    if (0 <= nr && nr < n && 0 <= nc && nc < m && grid[nr][nc] == '1') {
                        grid[nr][nc] = '0';
                        que.push(nr); que.push(nc);
                    }
                }
            }
        };
        
        int cnt = 0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) if (grid[r][c] == '1') {
                bfs(r, c);
                cnt++;
            }
        }
        return cnt;
    }
};
