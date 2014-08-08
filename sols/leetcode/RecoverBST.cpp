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
    TreeNode *first, *second;
    int swaps;
    void dfs(TreeNode *u) {
        if (!u) return;
        dfs(u->left);
        
        if (last && last->val > u->val) {
            if (++swaps == 1)
                first = last, second = u;
            else if (swaps == 2)
                second = u;
        }
        last = u;
        
        dfs(u->right);
    }
public:
    void recoverTree(TreeNode *root) {
        last = NULL, swaps = 0;
        dfs(root);
        swap(first->val, second->val);
    }
};
