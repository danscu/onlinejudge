/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode *last;
public:
    bool dfs(TreeNode *u) {
        if (!u) return true;
        bool ret = dfs(u->left);
        if (!ret) return ret;
        if (last && last->val >= u->val)
            return false;
        last = u;
        ret = dfs(u->right);
        if (!ret) return ret;
        return true;
    }
    
    bool isValidBST(TreeNode *root) {
        last = NULL;
        return dfs(root);
    }
};
