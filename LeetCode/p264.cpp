class Solution {
public:
    int nthUglyNumber(int n) {
        int arr[n];
        arr[0] = 1;
        int i = 0, j = 0, k = 0;
        for (int idx = 1; idx < n; ++idx) {
            int ri = arr[i] * 2, rj = arr[j] * 3, rk = arr[k] * 5;
            int minr = arr[idx] = min(ri, min(rj, rk));
            i += (ri == minr);
            j += (rj == minr);
            k += (rk == minr);
        }
        return arr[n - 1];
    }
};
