class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        long sum = 0, tmp = 0, n = A.size();
        for (long i = 0; i < n; ++i) {
            tmp += i * A[i];
            sum += A[i];
        }
        long res = tmp;
        for (long i = n - 1; i > 0; --i) {
            tmp = tmp + sum - n * A[i];
            res = max(res, tmp);
        }
        return res;
    }
};
