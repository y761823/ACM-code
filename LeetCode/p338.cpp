class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 2);
        for (int i = 0; i <= (num >> 1); ++i) {
            res[i << 1] = res[i];
            res[(i << 1) | 1] = res[i] + 1;
        }
        res.pop_back();
        return res;
    }
};
