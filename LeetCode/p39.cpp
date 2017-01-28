class Solution {
public:
    vector<vector<int>> res;
    vector<int> a, tmp;
    int target;

    void dfs(int sum, int pos) {
        if (sum == target) return res.push_back(tmp);
        for (int i = pos; i < a.size(); ++i) {
            if(sum + a[i] > target)
                continue;
            tmp.push_back(a[i]);
            dfs(sum + a[i], i);
            tmp.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        a = candidates;
        this->target = target;
        dfs(0, 0);
        return res;
    }
};
