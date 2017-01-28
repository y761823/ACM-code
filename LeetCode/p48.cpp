class Solution {
public:
    void rotate(vector<vector<int>>& mat) {
        int n = (int)mat.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n - i - 1; ++j) swap(mat[i][j], mat[n - j - 1][n - i - 1]);
        for (int i = (n + 1) / 2; i < n; ++i)
            swap(mat[i], mat[n - i - 1]);
    }
};
