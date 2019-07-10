class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;
        int n = matrix.size(), m = matrix.front().size();
        vector<vector<int>> maxs(n, vector<int>(m));
        int res = 0;
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < m; ++j) {
                maxs[i][j] = (matrix[i][j] == '1');
                if (i && j && matrix[i][j] == '1')
                    maxs[i][j] += min(maxs[i - 1][j - 1], min(maxs[i - 1][j], maxs[i][j - 1]));
                res = max(res, maxs[i][j]);
            }
        }
        return res * res;
    }
};
