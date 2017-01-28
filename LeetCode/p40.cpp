class Solution {
public:
    vector<vector<int>> res;
    vector<int> a, tmp;
    int target;

    void dfs(int sum, int lastPos) {
        if (sum == target) return res.push_back(tmp);
        for (int i = lastPos + 1; i < a.size(); ++i) {
            if (sum + a[i] > target)
                continue;
            if (i != lastPos + 1 && a[i] == a[i - 1])
                continue;
            tmp.push_back(a[i]);
            dfs(sum + a[i], i);
            tmp.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        a = candidates;
        this->target = target;
        a.push_back(-1);
        sort(a.begin(), a.end());
        dfs(0, 0);
        return res;
    }
};
