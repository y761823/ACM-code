class Solution {
public:
    string strs[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    string nums, now;
    vector<string> res;
    
    void dfs(size_t dep) {
        if (dep == nums.length())
            return res.push_back(now);
        int x = nums[dep] - '0';
        for (size_t i = 0; i < strs[x].length(); ++i) {
            now.push_back(strs[x][i]);
            dfs(dep + 1);
            now.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        nums = digits;
        if (!nums.empty())
            dfs(0);
        return res;
    }
};
