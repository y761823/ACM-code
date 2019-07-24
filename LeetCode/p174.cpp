class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size(), m = dungeon.front().size();
        vector<int> pre(m), cur(m);
        
        int last = 1;
        for (int j = m - 1; j >= 0; --j)
            last = cur[j] = max(1, last - dungeon[n - 1][j]);
        
        for (int i = n - 2; i >= 0; --i) {
            swap(pre, cur);
            for (int j = m - 1; j >= 0; --j) {
                int minh = pre[j];
                if (j + 1 < m)
                    minh = min(minh, cur[j + 1]);
                cur[j] = max(1, minh - dungeon[i][j]);
            }
        }
        return cur.front();
    }
};
