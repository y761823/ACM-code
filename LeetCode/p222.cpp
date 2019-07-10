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
    int countNodes(TreeNode* root) {
        if (!root)
             return 0;
        int depth = countDepth(root);
        int sum = (1 << (depth - 1));
        int l = 1, r = sum + 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (find(root, 1, sum, mid))
                l = mid + 1;
            else
                r = mid;
        }
        return sum + l - 2;
    }
    
    TreeNode* find(TreeNode* p, int l, int r, int k) {
        if (l == r)
            return p;
        int half = (r - l + 1) / 2;
        if (k < l + half)
            return find(p->left, l, r - half, k);
        else
            return find(p->right, l + half, r, k);
    }
    
    int countDepth(TreeNode* root) {
        int cnt = 0;
        while (root)
            root = root->left, cnt++;
        return cnt;
    }
};
