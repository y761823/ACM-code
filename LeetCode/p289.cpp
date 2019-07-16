class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        static const int fx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
        static const int fy[] = {1, 1, 1, 0, -1, -1, -1, 0};
        
        if (board.empty())
            return ;
        int n = board.size(), m = board.front().size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cnt = 0;
                for (int k = 0; k < 8; ++k) {
                    int ni = i + fx[k], nj = j + fy[k];
                    if (0 <= ni && ni < n && 0 <= nj && nj < m)
                        cnt += (board[ni][nj] & 1);
                }
                board[i][j] |= (board[i][j] ? (cnt == 2 || cnt == 3) : cnt == 3) << 1;
            }
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                board[i][j] >>= 1;
    }
};
