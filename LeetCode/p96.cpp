class Solution {
public:
    int numTrees(int n) {
        long long res = 1;
        for (int i = 1; i <= n; ++i)
            res = res * (2 * n - i + 1) / i;
        return (int)(res / (n + 1));
    }
};
