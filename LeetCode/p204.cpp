class Solution {
public:
    int countPrimes(int n) {
        vector<int> label(n), prime(n);
        int total = 0;
        for (int i = 2; i < n; ++i) {
            if (!label[i]) {
                prime[total++] = i;
                label[i] = total;
            }
            for (int j = 0; j < label[i]; ++j) {
                if (i * prime[j] >= n) break;
                label[i * prime[j]] = j + 1;
            }
        }
        return total;
    }
};
