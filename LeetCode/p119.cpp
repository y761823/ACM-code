class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res {1};
        for (int i = 1; i <= rowIndex; ++i)
            res.push_back((long long)res.back() * (rowIndex - i + 1) / i);
        return res;
    }
};
