class Solution {
public:
    int fx[4] = {0, 1, 0, -1};
    int fy[4] = {1, 0, -1, 0};

    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n));
        int cnt[2] = {n, n - 1}, f = 0, x = 0, y = -1, idx = 1;
        while (cnt[f & 1]) {
            for (int i = 0; i < cnt[f & 1]; ++i) {
                x += fx[f], y += fy[f];
                res[x][y] = idx++;
            }
            cnt[f & 1]--;
            f = (f + 1) & 3;
        }
        return res;
    }
};
