class Solution {
public:
    int uniquePaths(int m, int n) {
        --n, --m;
        if (n > m) swap(n, m);
        long long res = 1;
        for (int i = 1; i <= n; ++i)
            res = res * (n + m - i + 1) / i;
        return (int)res;
    }
};
