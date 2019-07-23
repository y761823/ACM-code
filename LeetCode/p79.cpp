class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board.front().empty())
            return word.empty();
        int n = board.size(), m = board.front().size();
        
        function<bool(int, int, size_t)> dfs = [&](int r, int c, size_t pos) {
            if (pos == word.size())
                return true;
            if (0 <= r && r < n && 0 <= c && c < m && board[r][c] == word[pos]) {
                board[r][c] = 0;
                if (dfs(r - 1, c, pos + 1)) return true;
                if (dfs(r, c - 1, pos + 1)) return true;
                if (dfs(r + 1, c, pos + 1)) return true;
                if (dfs(r, c + 1, pos + 1)) return true;
                board[r][c] = word[pos];
            }
            return false;
        };
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (dfs(i, j, 0)) return true;
        return false;
    }
};
