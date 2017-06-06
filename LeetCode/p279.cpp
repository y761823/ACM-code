class Solution {
    bool dfs(int rest, int dep, int maxs) {
        if (rest <= 0) {
            return rest == 0;
        } else {
            for (int i = maxs; i >= 1; --i) {
                int x = i * i;
                if (x * dep < rest)
                    break;
                if (dfs(rest - x, dep - 1, i))
                    return true;
            }
            return false;
        }
    }
public:
    int numSquares(int n) {
        int maxs = (int)sqrt(n + 0.5);
        for (int i = 1; i < n; ++i)
            if (dfs(n, i, maxs)) return i;
        return n;
    }
};
