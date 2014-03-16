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
    int min;

    void visit(TreeNode *root, int depth) {
        if (!root->left && !root->right)
            if (depth < min)
                min = depth;
        if (root->left)
            visit(root->left, depth + 1);
        if (root->right)
            visit(root->right, depth + 1);
    }

    int minDepth(TreeNode *root) {
        if (root == 0)
            return 0;

        min = INT_MAX;
        visit(root, 1);
        return min;
    }
};
