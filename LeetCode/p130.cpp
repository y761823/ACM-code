class Solution {
public:
    void solve(vector<vector<char>>& board) {
        static const int fr[] = {0, -1, 0, 1};
        static const int fc[] = {1, 0, -1, 0};
        
        if (board.empty() || board.front().empty())
            return ;
        
        int n = board.size(), m = board.front().size();
        auto color = [&](int sr, int sc) {
            queue<int> que;
            que.push(sr); que.push(sc);
            board[sr][sc] = 'o';
            while (!que.empty()) {
                int r = que.front(); que.pop();
                int c = que.front(); que.pop();
                for (int f = 0; f < 4; ++f) {
                    int nr = r + fr[f], nc = c + fc[f];
                    if (0 <= nr && nr < n && 0 <= nc && nc < m && board[nr][nc] == 'O') {
                        board[nr][nc] = 'o';
                        que.push(nr);
                        que.push(nc);
                    }
                }
            }
        };
        
        for (int r = 0; r < n; ++r) {
            if (board[r][0] == 'O') color(r, 0);
            if (board[r][m - 1] == 'O') color(r, m - 1);
        }
        for (int c = 0; c < m; ++c) {
            if (board[0][c] == 'O') color(0, c);
            if (board[n - 1][c] == 'O') color(n - 1, c);
        }
        
        for (auto& row : board) {
            for (char& c : row) {
                if (c == 'O') c = 'X';
                else if (c == 'o') c = 'O';
            }
        }
    }
};
