/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> res;
    
    void dfs(TreeNode* p, int sum, vector<int>& now) {
        if (!p) return;
        sum -= p->val;
        now.push_back(p->val);
        if (!p->left && !p->right) {
            if (!sum) res.push_back(now);
        } else {
            dfs(p->left, sum, now);
            dfs(p->right, sum, now);
        }
        now.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> now;
        dfs(root, sum, now);
        return res;
    }
};
