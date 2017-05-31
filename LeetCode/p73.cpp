class Solution {
typedef vector<vector<int>> Matrix;
    bool checkRowZero(Matrix& mat, int row) {
        for (size_t col = 0; col < mat[row].size(); ++col)
            if (mat[row][col] == 0) return true;
        return false;
    }
    
    bool checkColZero(Matrix& mat, int col) {
        for (size_t row = 0; row < mat.size(); ++row)
            if (mat[row][col] == 0) return true;
        return false;
    }
    
    void setRowZero(Matrix& mat, int row) {
        for (size_t col = 0; col < mat[row].size(); ++col)
            mat[row][col] = 0;
    }
    
    void setColZero(Matrix& mat, int col) {
        for (size_t row = 0; row < mat.size(); ++row)
            mat[row][col] = 0;
    }
public:
    void setZeroes(vector<vector<int>>& mat) {
        if (mat.empty() || mat.front().empty()) return ;
        int n = mat.size(), m = mat.front().size();
        bool firstRowZero = checkRowZero(mat, 0);
        for (int col = 0; col < m; ++col)
            if (checkColZero(mat, col))
                mat[0][col] = 0;
        for (int row = 1; row < n; ++row)
            if (checkRowZero(mat, row))
                setRowZero(mat, row);
        for (int col = 0; col < m; ++col)
            if (mat[0][col] == 0)
                setColZero(mat, col);
        if (firstRowZero)
            setRowZero(mat, 0);
    }
};
