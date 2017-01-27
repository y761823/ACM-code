class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> row(9, vector<bool>(9)), col(row), block(row);
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) if (board[i][j] != '.') {
                int id = board[i][j] - '1';
                if (row[i][id]) return false;
                if (col[j][id]) return false;
                if (block[i / 3 * 3 + j / 3][id]) return false;
                
                row[i][id] = true;
                col[j][id] = true;
                block[i / 3 * 3 + j / 3][id] = true;
            }
        }
        return true;
    }
};
