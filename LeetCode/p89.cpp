class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res{0};
        int bit = 1;
        while (n--) {
            for (int i = res.size() - 1; i >= 0; --i)
                res.push_back(res[i] | bit);
            bit <<= 1;
        }
        return res;
    }
};
