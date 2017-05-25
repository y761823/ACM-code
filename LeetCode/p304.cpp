class NumMatrix {
    vector<vector<int>> sum;
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.empty() || matrix.front().empty()) return ;
        int n = matrix.size(), m = matrix.front().size();
        sum = {n + 1, vector<int>(m + 1, 0)};
        for (int i = 1; i <= n; ++i) {
            partial_sum(matrix[i - 1].begin(), matrix[i - 1].end(), sum[i].begin() + 1);
            for (int j = 1; j <= m; ++j)
                sum[i][j] += sum[i - 1][j];
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] - sum[row1][col2 + 1] + sum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */
