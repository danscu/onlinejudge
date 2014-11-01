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
public:
    void traversal(vector<int> &res, TreeNode *u) {
        if (!u) return;
        traversal(res, u->left);
        res.push_back(u->val);
        traversal(res, u->right);
    }

    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        traversal(res, root);
        return res;
    }
};
