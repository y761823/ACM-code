class Solution {
public:
    int fx[4] = {0, 1, 0, -1};
    int fy[4] = {1, 0, -1, 0};

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty() || matrix.front().empty())
            return res;
            
        int n = matrix.size(), m = matrix.front().size(), x = 0, y = -1;
        int cnt[2] = {m, n - 1}, f = 0;
        while (cnt[f & 1]) {
            for (int i = 0; i < cnt[f & 1]; ++i) {
                x += fx[f], y += fy[f];
                res.push_back(matrix[x][y]);
            }
            cnt[f & 1]--;
            f = (f + 1) & 3;
        }
        return res;
    }
};
