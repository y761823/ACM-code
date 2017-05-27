class Solution {
    vector<vector<int>> res;
    vector<int> arr;
    int n, k;
    
    void dfs(int idx, int minv) {
        if (idx == k) {
            res.push_back(arr);
        } else {
            int ed = (n - (k - idx) + 1);
            for (int i = minv; i < ed; ++i) {
                arr[idx] = i + 1;
                dfs(idx + 1, i + 1);
            }
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        this->n = n; this->k = k;
        arr.resize(k);
        dfs(0, 0);
        return res;
    }
};
