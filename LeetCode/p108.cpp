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
    typedef vector<int>::iterator Iter;

    TreeNode* buildTree(Iter st, Iter ed) {
        if (st >= ed) return nullptr;
        Iter mid = st + (ed - st - 1) / 2;
        TreeNode* p = new TreeNode(*mid);
        p->left = buildTree(st, mid);
        p->right = buildTree(mid + 1, ed);
        return p;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildTree(nums.begin(), nums.end());
    }
};
